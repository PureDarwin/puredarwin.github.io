/* SPDX-License-Identifier: GPL-2.0-or-later OR MIT
 *
 * Copyright (c) 2026 PureDarwin Project
 *
 * pdnews, list and create PureDarwin news entries.
 */

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#define NEWS_DIR "src/news"
#define NEWS_INDEX "src/news/_News.md"
#define SUMMARY "src/SUMMARY.md"
#define HOME_PAGE "src/index.html"
#define HOME_BEGIN "<!-- pdnews:latest -->"
#define HOME_END "<!-- /pdnews:latest -->"
#define HOME_COUNT 3

static const char *months[12] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

static void die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	fputs("pdnews: ", stderr);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	va_end(ap);
	exit(1);
}

static void *xmalloc(size_t n)
{
	void *p = malloc(n);

	if (!p)
		die("out of memory");
	return p;
}

static char *xstrdup(const char *s)
{
	size_t n = strlen(s) + 1;
	char *p = xmalloc(n);

	memcpy(p, s, n);
	return p;
}

/* Growable byte buffer. */
struct buf {
	char *data;
	size_t len;
	size_t cap;
};

static void buf_grow(struct buf *b, size_t extra)
{
	if (b->len + extra + 1 <= b->cap)
		return;
	while (b->cap < b->len + extra + 1)
		b->cap = b->cap ? b->cap * 2 : 256;
	b->data = realloc(b->data, b->cap);
	if (!b->data)
		die("out of memory");
}

static void buf_add(struct buf *b, const char *s, size_t n)
{
	buf_grow(b, n);
	memcpy(b->data + b->len, s, n);
	b->len += n;
	b->data[b->len] = '\0';
}

static void buf_puts(struct buf *b, const char *s)
{
	buf_add(b, s, strlen(s));
}

static void buf_printf(struct buf *b, const char *fmt, ...)
{
	char tmp[4096];
	va_list ap;
	int n;

	va_start(ap, fmt);
	n = vsnprintf(tmp, sizeof(tmp), fmt, ap);
	va_end(ap);
	if (n < 0 || (size_t)n >= sizeof(tmp))
		die("formatted string too long");
	buf_add(b, tmp, (size_t)n);
}

static void buf_free(struct buf *b)
{
	free(b->data);
	b->data = NULL;
	b->len = b->cap = 0;
}

/* Join root and a repo-relative path into dst, dying rather than truncating. */
static void joinpath(char *dst, size_t cap, const char *root, const char *rel)
{
	int n = snprintf(dst, cap, "%s/%s", root, rel);

	if (n < 0 || (size_t)n >= cap)
		die("path too long: %s/%s", root, rel);
}

static char *read_file(const char *path, size_t *lenp)
{
	FILE *f = fopen(path, "rb");
	struct buf b = {0};
	char chunk[8192];
	size_t n;

	if (!f)
		die("cannot open %s: %s", path, strerror(errno));
	while ((n = fread(chunk, 1, sizeof(chunk), f)) > 0)
		buf_add(&b, chunk, n);
	fclose(f);
	if (lenp)
		*lenp = b.len;
	if (!b.data)
		b.data = xstrdup("");
	return b.data;
}

static void write_file(const char *path, const char *data, size_t len)
{
	FILE *f = fopen(path, "wb");

	if (!f)
		die("cannot write %s: %s", path, strerror(errno));
	if (len && fwrite(data, 1, len, f) != len)
		die("short write on %s", path);
	if (fclose(f) != 0)
		die("cannot close %s: %s", path, strerror(errno));
}

/*
 * Fold common typographic UTF-8 punctuation to ASCII. Anything else outside
 * ASCII is rejected so we never ship characters a plain terminal cannot show.
 */
struct fold {
	const char *utf8;
	const char *ascii;
};

static const struct fold folds[] = {
	{ "\xe2\x80\x98", "'" },	/* left single quote */
	{ "\xe2\x80\x99", "'" },	/* right single quote */
	{ "\xe2\x80\x9c", "\"" },	/* left double quote */
	{ "\xe2\x80\x9d", "\"" },	/* right double quote */
	{ "\xe2\x80\x93", "-" },	/* en dash */
	{ "\xe2\x80\x94", "-" },	/* em dash */
	{ "\xe2\x80\xa6", "..." },	/* ellipsis */
	{ "\xe2\x80\xa2", "*" },	/* bullet */
	{ "\xc2\xa0", " " },		/* no-break space */
	{ "\xc2\xad", "" },		/* soft hyphen */
	{ NULL, NULL }
};

static int allow_utf8;

static char *to_ascii(const char *s, const char *what)
{
	struct buf out = {0};
	const char *p = s;

	while (*p) {
		unsigned char c = (unsigned char)*p;
		int folded = 0;
		int i;

		if (c < 0x80) {
			buf_add(&out, p, 1);
			p++;
			continue;
		}
		for (i = 0; folds[i].utf8; i++) {
			size_t n = strlen(folds[i].utf8);

			if (strncmp(p, folds[i].utf8, n) == 0) {
				buf_puts(&out, folds[i].ascii);
				p += n;
				folded = 1;
				break;
			}
		}
		if (!folded && allow_utf8) {
			buf_add(&out, p, 1);
			p++;
		} else if (!folded) {
			die("%s contains a non-ASCII character at byte %zu (0x%02x); use plain ASCII",
			    what, (size_t)(p - s), c);
		}
	}
	if (!out.data)
		out.data = xstrdup("");
	return out.data;
}

static void rstrip(char *s)
{
	size_t n = strlen(s);

	while (n && (s[n - 1] == '\n' || s[n - 1] == '\r' || s[n - 1] == ' ' ||
		     s[n - 1] == '\t'))
		s[--n] = '\0';
}

static const char *skip_ws(const char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return s;
}

/* Copy one line starting at *p, advancing *p past the newline. */
static char *take_line(const char **p)
{
	const char *start = *p;
	const char *end = strchr(start, '\n');
	size_t n;
	char *line;

	if (!end) {
		n = strlen(start);
		*p = start + n;
	} else {
		n = (size_t)(end - start);
		*p = end + 1;
	}
	line = xmalloc(n + 1);
	memcpy(line, start, n);
	line[n] = '\0';
	rstrip(line);
	return line;
}

struct entry {
	char *slug;
	char *path;		/* repo-relative markdown path */
	char *title;
	char *date;		/* as written, e.g. "January 3, 2026" */
	char *iso_date;		/* YYYY-MM-DD, empty if unparsed */
	char *author;
	char *image;
	char *summary;		/* from the news index, may be empty */
};

static int parse_month(const char *name)
{
	int i;

	for (i = 0; i < 12; i++)
		if (strncmp(name, months[i], strlen(months[i])) == 0)
			return i + 1;
	return 0;
}

/* "January 3, 2026 - author..." -> date, iso date and author. */
static int parse_dateline(const char *line, struct entry *e)
{
	const char *p = skip_ws(line);
	const char *sep;
	int month, day, year;
	char datebuf[64], isobuf[16];
	size_t n;

	month = parse_month(p);
	if (!month)
		return 0;
	p += strlen(months[month - 1]);
	p = skip_ws(p);
	if (!isdigit((unsigned char)*p))
		return 0;
	day = atoi(p);
	while (isdigit((unsigned char)*p))
		p++;
	if (*p == ',')
		p++;
	p = skip_ws(p);
	if (!isdigit((unsigned char)*p))
		return 0;
	year = atoi(p);
	while (isdigit((unsigned char)*p))
		p++;

	n = (size_t)(p - line);
	if (n >= sizeof(datebuf))
		n = sizeof(datebuf) - 1;
	memcpy(datebuf, line, n);
	datebuf[n] = '\0';
	rstrip(datebuf);
	e->date = xstrdup(skip_ws(datebuf));

	snprintf(isobuf, sizeof(isobuf), "%04d-%02d-%02d", year, month, day);
	e->iso_date = xstrdup(isobuf);

	p = skip_ws(p);
	sep = strstr(p, "- ");
	if (sep == p)
		p += 2;
	e->author = xstrdup(skip_ws(p));
	return 1;
}

/* Pull the alt-less target out of the first "![alt](target)" on a line. */
static char *parse_image(const char *line)
{
	const char *open = strstr(line, "](");
	const char *close;

	if (strncmp(skip_ws(line), "![", 2) != 0 || !open)
		return NULL;
	open += 2;
	close = strchr(open, ')');
	if (!close)
		return NULL;
	return strndup(open, (size_t)(close - open));
}

static void entry_parse_file(struct entry *e, const char *root)
{
	char full[4096];
	char *text;
	const char *p;
	int lines = 0;

	joinpath(full, sizeof(full), root, e->path);
	text = read_file(full, NULL);
	p = text;
	while (*p && lines < 20) {
		char *line = take_line(&p);

		lines++;
		if (!e->title && strncmp(line, "# ", 2) == 0)
			e->title = xstrdup(skip_ws(line + 2));
		else if (!e->date && line[0])
			parse_dateline(line, e);
		if (!e->image) {
			char *img = parse_image(line);

			if (img)
				e->image = img;
		}
		free(line);
	}
	free(text);
	if (!e->title)
		e->title = xstrdup(e->slug);
	if (!e->date)
		e->date = xstrdup("");
	if (!e->iso_date)
		e->iso_date = xstrdup("");
	if (!e->author)
		e->author = xstrdup("");
	if (!e->image)
		e->image = xstrdup("");
	e->summary = xstrdup("");
}

/*
 * Summaries live only in the news index, as:
 *   ### [Title](/news/Slug.md)
 *   January 3, 2026 - "summary text"
 */
static void attach_summaries(struct entry *list, size_t n, const char *root)
{
	char full[4096];
	char *text;
	const char *p;
	char *pending = NULL;

	joinpath(full, sizeof(full), root, NEWS_INDEX);
	if (access(full, R_OK) != 0)
		return;
	text = read_file(full, NULL);
	p = text;
	while (*p) {
		char *line = take_line(&p);
		char *open = strstr(line, "](/news/");

		if (strncmp(line, "### [", 5) == 0 && open) {
			char *slug = xstrdup(open + strlen("](/news/"));
			char *dot = strstr(slug, ".md");

			if (dot)
				*dot = '\0';
			free(pending);
			pending = slug;
		} else if (pending) {
			char *q1 = strchr(line, '"');
			char *q2 = q1 ? strrchr(line, '"') : NULL;

			if (q1 && q2 && q2 > q1) {
				size_t i;

				for (i = 0; i < n; i++) {
					if (strcmp(list[i].slug, pending) != 0)
						continue;
					free(list[i].summary);
					list[i].summary =
						strndup(q1 + 1, (size_t)(q2 - q1 - 1));
					break;
				}
				free(pending);
				pending = NULL;
			}
		}
		free(line);
	}
	free(pending);
	free(text);
}

static int entry_cmp(const void *a, const void *b)
{
	const struct entry *x = a, *y = b;
	int c = strcmp(y->iso_date, x->iso_date);	/* newest first */

	return c ? c : strcmp(x->slug, y->slug);
}

static struct entry *collect(const char *root, size_t *countp)
{
	char dirpath[4096];
	DIR *d;
	struct dirent *de;
	struct entry *list = NULL;
	size_t n = 0, cap = 0;

	joinpath(dirpath, sizeof(dirpath), root, NEWS_DIR);
	d = opendir(dirpath);
	if (!d)
		die("cannot read %s: %s", dirpath, strerror(errno));
	while ((de = readdir(d))) {
		const char *name = de->d_name;
		size_t len = strlen(name);
		struct entry e = {0};
		char rel[4096];

		if (name[0] == '.' || name[0] == '_')
			continue;
		if (len < 4 || strcmp(name + len - 3, ".md") != 0)
			continue;
		if (n == cap) {
			cap = cap ? cap * 2 : 16;
			list = realloc(list, cap * sizeof(*list));
			if (!list)
				die("out of memory");
		}
		e.slug = strndup(name, len - 3);
		joinpath(rel, sizeof(rel), NEWS_DIR, name);
		e.path = xstrdup(rel);
		entry_parse_file(&e, root);
		list[n++] = e;
	}
	closedir(d);
	attach_summaries(list, n, root);
	qsort(list, n, sizeof(*list), entry_cmp);
	*countp = n;
	return list;
}

static void json_string(struct buf *b, const char *s)
{
	buf_puts(b, "\"");
	for (; *s; s++) {
		unsigned char c = (unsigned char)*s;

		switch (c) {
		case '"':
			buf_puts(b, "\\\"");
			break;
		case '\\':
			buf_puts(b, "\\\\");
			break;
		case '\n':
			buf_puts(b, "\\n");
			break;
		case '\t':
			buf_puts(b, "\\t");
			break;
		case '\r':
			buf_puts(b, "\\r");
			break;
		default:
			if (c < 0x20)
				buf_printf(b, "\\u%04x", c);
			else
				buf_add(b, (const char *)&c, 1);
		}
	}
	buf_puts(b, "\"");
}

static void json_field(struct buf *b, const char *key, const char *val, int last)
{
	buf_printf(b, "    \"%s\": ", key);
	json_string(b, val);
	buf_puts(b, last ? "\n" : ",\n");
}

static int cmd_list(const char *root, int as_json)
{
	size_t n, i;
	struct entry *list = collect(root, &n);

	if (!as_json) {
		for (i = 0; i < n; i++)
			printf("%-12s  %-40s  %s\n",
			       list[i].iso_date[0] ? list[i].iso_date : "-",
			       list[i].title, list[i].path);
		return 0;
	}

	struct buf b = {0};

	buf_puts(&b, "[\n");
	for (i = 0; i < n; i++) {
		buf_puts(&b, "  {\n");
		json_field(&b, "slug", list[i].slug, 0);
		json_field(&b, "title", list[i].title, 0);
		json_field(&b, "date", list[i].date, 0);
		json_field(&b, "iso_date", list[i].iso_date, 0);
		json_field(&b, "author", list[i].author, 0);
		json_field(&b, "summary", list[i].summary, 0);
		json_field(&b, "image", list[i].image, 0);
		json_field(&b, "path", list[i].path, 1);
		buf_printf(&b, "  }%s\n", i + 1 == n ? "" : ",");
	}
	buf_puts(&b, "]\n");
	fwrite(b.data, 1, b.len, stdout);
	buf_free(&b);
	return 0;
}

/* "My Title: Part Two" -> "My-Title-Part-Two" */
static char *slugify(const char *title)
{
	struct buf b = {0};
	int prev_dash = 1;
	const char *p;

	for (p = title; *p; p++) {
		unsigned char c = (unsigned char)*p;

		if (isalnum(c)) {
			buf_add(&b, (const char *)&c, 1);
			prev_dash = 0;
		} else if (!prev_dash) {
			buf_puts(&b, "-");
			prev_dash = 1;
		}
	}
	if (b.len && b.data[b.len - 1] == '-')
		b.data[--b.len] = '\0';
	if (!b.len)
		die("cannot derive a slug from the title; pass --slug");
	return b.data;
}

/* Accepts YYYY-MM-DD and renders "January 3, 2026". */
static char *pretty_date(const char *iso)
{
	int y, m, d;
	char out[64];

	if (sscanf(iso, "%d-%d-%d", &y, &m, &d) != 3 || m < 1 || m > 12 ||
	    d < 1 || d > 31)
		die("date must be YYYY-MM-DD, got \"%s\"", iso);
	snprintf(out, sizeof(out), "%s %d, %d", months[m - 1], d, y);
	return xstrdup(out);
}

static char *today_iso(void)
{
	time_t t = time(NULL);
	struct tm tm;
	char buf[16];

	localtime_r(&t, &tm);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
	return xstrdup(buf);
}

/* Insert `ins` before the first line that starts with `marker`, else append. */
static char *insert_before(const char *text, const char *marker,
			   const char *ins, const char *fallback_after)
{
	struct buf out = {0};
	const char *p = text;
	int done = 0;
	int seen_anchor = fallback_after ? 0 : 1;

	while (*p) {
		const char *line_start = p;
		char *line = take_line(&p);

		if (!done && fallback_after && !seen_anchor &&
		    strncmp(line, fallback_after, strlen(fallback_after)) == 0) {
			seen_anchor = 1;
			buf_add(&out, line_start, (size_t)(p - line_start));
			free(line);
			continue;
		}
		if (!done && seen_anchor &&
		    strncmp(line, marker, strlen(marker)) == 0) {
			buf_puts(&out, ins);
			done = 1;
		}
		buf_add(&out, line_start, (size_t)(p - line_start));
		free(line);
	}
	if (!done)
		buf_puts(&out, ins);
	return out.data ? out.data : xstrdup("");
}

static void update_index(const char *root, const char *slug, const char *title,
			 const char *date, const char *summary)
{
	char full[4096];
	char *text, *updated;
	struct buf ins = {0};

	joinpath(full, sizeof(full), root, NEWS_INDEX);
	text = read_file(full, NULL);
	buf_printf(&ins, "### [%s](/news/%s.md)\n", title, slug);
	buf_printf(&ins, "%s - \"%s\"\n\n\n", date, summary);
	updated = insert_before(text, "### [", ins.data, NULL);
	write_file(full, updated, strlen(updated));
	free(text);
	free(updated);
	buf_free(&ins);
}

static void update_summary(const char *root, const char *slug, const char *title)
{
	char full[4096];
	char *text, *updated;
	struct buf ins = {0};

	joinpath(full, sizeof(full), root, SUMMARY);
	text = read_file(full, NULL);
	buf_printf(&ins, "\t- [%s](news/%s.md)\n", title, slug);
	updated = insert_before(text, "\t- [", ins.data, "- [News](news/_News.md)");
	write_file(full, updated, strlen(updated));
	free(text);
	free(updated);
	buf_free(&ins);
}

/*
 * The landing page shows the newest few entries. It is generated from the same
 * data as the news index rather than kept by hand, so the two cannot disagree.
 */
static void update_home(const char *root, struct entry *list, size_t n)
{
	char full[4096];
	char *text;
	const char *begin, *end;
	struct buf out = {0};
	size_t i, limit = n < HOME_COUNT ? n : HOME_COUNT;

	joinpath(full, sizeof(full), root, HOME_PAGE);
	if (access(full, R_OK) != 0)
		return;
	text = read_file(full, NULL);

	begin = strstr(text, HOME_BEGIN);
	end = begin ? strstr(begin, HOME_END) : NULL;
	if (!begin || !end) {
		free(text);
		fprintf(stderr, "pdnews: no %s block in %s, leaving it alone\n",
			HOME_BEGIN, HOME_PAGE);
		return;
	}

	buf_add(&out, text, (size_t)(begin - text));
	buf_puts(&out, HOME_BEGIN "\n");
	buf_puts(&out, "      <ul class=\"mt-5 space-y-4\">\n");
	for (i = 0; i < limit; i++) {
		buf_puts(&out, "        <li>\n");
		buf_printf(&out,
			   "          <div class=\"text-sm text-pd-muted\">%s</div>\n",
			   list[i].date);
		buf_printf(&out,
			   "          <a href=\"/news/%s.html\" class=\"font-medium text-pd-ink hover:text-pd-blue\">\n",
			   list[i].slug);
		buf_printf(&out, "            %s\n", list[i].title);
		buf_puts(&out, "          </a>\n");
		buf_puts(&out, "        </li>\n");
	}
	buf_puts(&out, "      </ul>\n      ");
	buf_puts(&out, end);

	write_file(full, out.data, out.len);
	buf_free(&out);
	free(text);
}

static void sync_home(const char *root)
{
	size_t n;
	struct entry *list = collect(root, &n);

	update_home(root, list, n);
}

static int cmd_new(const char *root, int argc, char **argv)
{
	const char *title = NULL, *author = NULL, *summary = NULL;
	const char *image = NULL, *slug_arg = NULL, *date_arg = NULL;
	const char *body_file = NULL;
	int force = 0, i;
	char *slug, *iso, *date, *body = NULL;
	char path[4096], full[4096];
	struct buf doc = {0};
	struct stat st;

	for (i = 0; i < argc; i++) {
		const char *a = argv[i];
		const char *val = (i + 1 < argc) ? argv[i + 1] : NULL;

#define OPT(name, dest) \
	if (strcmp(a, name) == 0) { \
		if (!val) die("%s needs a value", name); \
		dest = val; i++; continue; \
	}
		OPT("--title", title)
		OPT("--author", author)
		OPT("--summary", summary)
		OPT("--image", image)
		OPT("--slug", slug_arg)
		OPT("--date", date_arg)
		OPT("--body-file", body_file)
#undef OPT
		if (strcmp(a, "--allow-utf8") == 0) {
			allow_utf8 = 1;
			continue;
		}
		if (strcmp(a, "--force") == 0) {
			force = 1;
			continue;
		}
		die("unknown option for \"new\": %s", a);
	}

	if (!title)
		die("--title is required");
	title = to_ascii(title, "title");
	author = to_ascii(author ? author : "PD-Team", "author");
	summary = to_ascii(summary ? summary : "", "summary");
	image = to_ascii(image ? image : "", "image path");
	iso = date_arg ? xstrdup(date_arg) : today_iso();
	date = pretty_date(iso);
	slug = slug_arg ? to_ascii(slug_arg, "slug") : slugify(title);

	if (body_file) {
		char *raw = read_file(body_file, NULL);

		body = to_ascii(raw, "body file");
		free(raw);
	}

	{
		char leaf[512];

		if (snprintf(leaf, sizeof(leaf), "%s.md", slug) >= (int)sizeof(leaf))
			die("slug too long");
		joinpath(path, sizeof(path), NEWS_DIR, leaf);
	}
	joinpath(full, sizeof(full), root, path);
	if (!force && stat(full, &st) == 0)
		die("%s already exists (use --force to overwrite)", path);

	buf_printf(&doc, "# %s\n\n", title);
	buf_printf(&doc, "%s - %s\n\n", date, author);
	if (image[0])
		buf_printf(&doc, "![%s](%s)\n\n", title, image);
	if (body)
		buf_puts(&doc, body);
	else if (summary[0])
		buf_printf(&doc, "%s\n", summary);
	else
		buf_puts(&doc, "Write the article body here.\n");
	if (doc.len && doc.data[doc.len - 1] != '\n')
		buf_puts(&doc, "\n");

	write_file(full, doc.data, doc.len);
	update_index(root, slug, title, date, summary[0] ? summary : title);
	update_summary(root, slug, title);

	sync_home(root);

	printf("created %s\n", path);
	printf("updated %s\n", NEWS_INDEX);
	printf("updated %s\n", SUMMARY);
	printf("updated %s\n", HOME_PAGE);

	buf_free(&doc);
	free(body);
	return 0;
}

static void usage(FILE *out)
{
	fputs(
"usage: pdnews [--root DIR] <command> [options]\n"
"\n"
"commands:\n"
"  list [--json]        list news entries, newest first\n"
"  new --title TITLE [--date YYYY-MM-DD] [--author NAME] [--summary TEXT]\n"
"      [--image PATH] [--slug SLUG] [--body-file FILE] [--allow-utf8]\n"
"      [--force]\n"
"                       create an entry and link it from the news index\n"
"                       and SUMMARY.md\n"
"  sync                 regenerate the landing page's latest-news block\n"
"  help                 show this text\n"
"\n"
"--root defaults to $PDNEWS_ROOT, else the current directory. Text is\n"
"written as plain ASCII; typographic punctuation is folded and any other\n"
"non-ASCII input is rejected unless --allow-utf8 is given.\n", out);
}

int main(int argc, char **argv)
{
	const char *root = getenv("PDNEWS_ROOT");
	int i = 1;

	if (!root || !*root)
		root = ".";
	while (i < argc && strcmp(argv[i], "--root") == 0) {
		if (i + 1 >= argc)
			die("--root needs a value");
		root = argv[i + 1];
		i += 2;
	}
	if (i >= argc) {
		usage(stderr);
		return 2;
	}

	const char *cmd = argv[i++];

	if (strcmp(cmd, "help") == 0 || strcmp(cmd, "--help") == 0) {
		usage(stdout);
		return 0;
	}
	if (strcmp(cmd, "list") == 0) {
		int as_json = 0;

		for (; i < argc; i++) {
			if (strcmp(argv[i], "--json") == 0)
				as_json = 1;
			else
				die("unknown option for \"list\": %s", argv[i]);
		}
		return cmd_list(root, as_json);
	}
	if (strcmp(cmd, "new") == 0)
		return cmd_new(root, argc - i, argv + i);
	if (strcmp(cmd, "sync") == 0) {
		if (i < argc)
			die("unknown option for \"sync\": %s", argv[i]);
		sync_home(root);
		printf("updated %s\n", HOME_PAGE);
		return 0;
	}

	die("unknown command \"%s\" (try \"pdnews help\")", cmd);
	return 2;
}
