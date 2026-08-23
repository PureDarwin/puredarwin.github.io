#!/bin/sh
# Hash the published preview images and write the checksums into the site.
#
# The hashes are taken from the served files rather than from a local build,
# so what ends up on the page is what a visitor actually downloads.
set -eu

BASE_URL="${PDIMAGES_BASE_URL:-https://internal.lab004.dev/private/images}"
ROOT="${PDIMAGES_ROOT:-.}"

BEGIN_MARK="<!-- pdimages:list -->"
END_MARK="<!-- /pdimages:list -->"

ICON_DISK='<svg class="mt-1 h-4 w-4 shrink-0 text-pd-muted" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true"><path d="M12 2v8" /> <path d="m16 6-4 4-4-4" /> <rect width="20" height="8" x="2" y="14" rx="2" /> <path d="M6 18h.01" /> <path d="M10 18h.01" /></svg>'
ICON_VIDEO='<svg class="mt-1 h-4 w-4 shrink-0 text-pd-muted" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true"><rect width="18" height="18" x="3" y="3" rx="2" /> <path d="M7 3v18" /> <path d="M3 7.5h4" /> <path d="M3 12h18" /> <path d="M3 16.5h4" /> <path d="M17 3v18" /> <path d="M17 7.5h4" /> <path d="M17 16.5h4" /></svg>'

usage() {
	cat <<'EOF'
usage: pdimages <command>

  hash    print SHA256SUMS lines for every file in images.list
  sync    write src/SHA256SUMS and update the list in src/index.html

--root defaults to $PDIMAGES_ROOT, else the current directory. The download
base URL comes from $PDIMAGES_BASE_URL. Both files are read from and written
as plain ASCII.
EOF
}

manifest() {
	if [ -n "${PDIMAGES_MANIFEST:-}" ]; then
		printf '%s\n' "$PDIMAGES_MANIFEST"
		return
	fi
	for candidate in \
		"$ROOT/tools/pdimages/images.list" \
		"$(dirname "$0")/images.list"
	do
		if [ -f "$candidate" ]; then
			printf '%s\n' "$candidate"
			return
		fi
	done
	echo "pdimages: cannot find images.list" >&2
	exit 1
}

# Strips comments and blank lines so the callers can just read fields.
records() {
	sed -e '/^[[:space:]]*#/d' -e '/^[[:space:]]*$/d' "$(manifest)"
}

human_size() {
	awk -v b="$1" 'BEGIN {
		if (b >= 1073741824) { printf "%.1f GiB", b / 1073741824 }
		else if (b >= 1048576) { printf "%.0f MiB", b / 1048576 }
		else { printf "%d bytes", b }
	}'
}

remote_size() {
	curl -fsS -o /dev/null -I -w '%{header_json}' "$1" \
		| tr -d ' "' | sed -n 's/.*content-length:\[\([0-9]*\)\].*/\1/p'
}

hash_one() {
	curl -fsS "$1" | sha256sum | cut -d' ' -f1
}

cmd_hash() {
	records | while IFS='	' read -r file kind desc; do
		[ -n "$file" ] || continue
		printf '%s  %s\n' "$(hash_one "$BASE_URL/$file")" "$file"
	done
}

cmd_sync() {
	index="$ROOT/src/index.html"
	sums="$ROOT/src/SHA256SUMS"
	if [ ! -f "$index" ]; then
		echo "pdimages: no src/index.html under $ROOT" >&2
		exit 1
	fi

	tmp_sums=$(mktemp)
	tmp_list=$(mktemp)
	trap 'rm -f "$tmp_sums" "$tmp_list"' EXIT

	records | while IFS='	' read -r file kind desc; do
		[ -n "$file" ] || continue
		url="$BASE_URL/$file"
		echo "pdimages: hashing $file" >&2
		size=$(remote_size "$url")
		sum=$(hash_one "$url")
		printf '%s  %s\n' "$sum" "$file" >> "$tmp_sums"

		case "$kind" in
			video) icon=$ICON_VIDEO ;;
			*)     icon=$ICON_DISK ;;
		esac

		{
			printf '        <li class="flex gap-3">\n'
			printf '          %s\n' "$icon"
			printf '          <div class="min-w-0">\n'
			printf '          <a href="%s"\n' "$url"
			printf '            class="font-medium text-pd-blue hover:underline">%s</a>\n' "$file"
			printf '          <span class="block text-sm text-pd-muted">%s</span>\n' "$desc"
			printf '          <span class="mt-1 block break-all font-mono text-xs text-pd-muted">%s <span class="select-all">%s</span></span>\n' \
				"$(human_size "$size")" "$sum"
			printf '          </div>\n'
			printf '        </li>\n'
		} >> "$tmp_list"
	done

	cp "$tmp_sums" "$sums"

	awk -v begin="$BEGIN_MARK" -v end="$END_MARK" -v listfile="$tmp_list" '
		index($0, begin) { print; while ((getline line < listfile) > 0) print line; skip = 1; next }
		index($0, end)   { skip = 0 }
		!skip            { print }
	' "$index" > "$index.new"
	mv "$index.new" "$index"

	echo "pdimages: wrote $sums and updated $index" >&2
}

case "${1:-}" in
	hash) shift; cmd_hash "$@" ;;
	sync) shift; cmd_sync "$@" ;;
	-h|--help|help|"") usage ;;
	*) usage >&2; exit 1 ;;
esac
