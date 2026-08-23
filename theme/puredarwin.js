document.addEventListener("DOMContentLoaded", () => {
  const menu = document.querySelector("#mdbook-menu-bar");

  if (!menu) {
    return;
  }

  // mdBook nests the masthead in its sidebar-shifted page wrapper. Moving the
  // same node preserves all built-in event handlers while anchoring it to the
  // viewport instead of the current sidebar width.
  document.body.appendChild(menu);

  const outline = document.querySelector("#mdbook-sidebar .on-this-page");
  const outlineHeadings = Array.from(
    document.querySelectorAll("main h2, main h3, main h4, main h5, main h6"),
  );

  // Index pages use headings as links to other pages. mdBook mistakes those
  // for sections of the current page and inserts a redundant outline.
  if (
    outline &&
    outlineHeadings.length > 0 &&
    outlineHeadings.every((heading) =>
      heading.querySelector(":scope > a.header + a"),
    )
  ) {
    outline.remove();
  }

  // mdBook offers six themes (Auto, Light, Rust, Coal, Navy, Ayu) but this
  // theme only defines two schemes, so five of those entries are duplicates
  // and the picker icon changes state for no useful reason. Replace the whole
  // control with a two-state toggle that writes the same localStorage key, so
  // the handbook and the landing page stay in step.
  const DARK_THEME = "navy";
  const LIGHT_THEME = "light";
  const SUN =
    '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" ' +
    'stroke="currentColor" stroke-width="2" stroke-linecap="round" ' +
    'stroke-linejoin="round"><circle cx="12" cy="12" r="4"/><path d="M12 2v2"/>' +
    '<path d="M12 20v2"/><path d="m4.93 4.93 1.41 1.41"/>' +
    '<path d="m17.66 17.66 1.41 1.41"/><path d="M2 12h2"/><path d="M20 12h2"/>' +
    '<path d="m6.34 17.66-1.41 1.41"/><path d="m19.07 4.93-1.41 1.41"/></svg>';
  const MOON =
    '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" ' +
    'stroke="currentColor" stroke-width="2" stroke-linecap="round" ' +
    'stroke-linejoin="round"><path d="M20.985 12.486a9 9 0 1 1-9.473-9.472' +
    'c.405-.022.617.46.402.803a6 6 0 0 0 8.268 8.268c.344-.215.825-.004.803.401"/></svg>';

  const picker = document.querySelector("#mdbook-theme-toggle");

  if (picker) {
    const isDark = () => !document.documentElement.classList.contains("light");

    const toggle = document.createElement("button");
    toggle.type = "button";
    toggle.className = picker.className;
    toggle.id = "pd-theme-toggle";

    const paint = (dark) => {
      toggle.innerHTML = '<span class="fa-svg">' + (dark ? SUN : MOON) + "</span>";
      const next = dark ? "light" : "dark";
      toggle.title = "Switch to " + next + " theme";
      toggle.setAttribute("aria-label", toggle.title);
    };

    paint(isDark());

    toggle.addEventListener("click", () => {
      const dark = !isDark();
      const root = document.documentElement;
      root.classList.remove("light", "rust", "coal", "navy", "ayu");
      root.classList.add(dark ? DARK_THEME : LIGHT_THEME);
      try {
        localStorage.setItem(
          "mdbook-theme",
          JSON.stringify(dark ? DARK_THEME : LIGHT_THEME),
        );
      } catch (e) {
        /* storage disabled; the choice just will not persist */
      }
      paint(dark);
    });

    picker.replaceWith(toggle);

    // Leftmost in the group, ahead of the sidebar button, so it lands in the
    // same place as the landing page's toggle.
    const leftButtons = menu.querySelector(".left-buttons");
    if (leftButtons) {
      leftButtons.prepend(toggle);
    }
    const list = document.querySelector("#mdbook-theme-list");
    if (list) {
      list.remove();
    }
  }

  // Same links as the landing page, in the same corner, so moving between the
  // two halves of the site does not move the navigation.
  if (!menu.querySelector("#pd-nav")) {
    const root = typeof path_to_root === "string" ? path_to_root : "";
    const links = [
      ["Home", root + "index.html"],
      ["Handbook", root + "handbook/_Handbook.html"],
      ["News", root + "news/_News.html"],
      ["Get it", root + "index.html#get-it"],
      ["GitHub", "https://github.com/PureDarwin/PureDarwin"],
      ["Archive", root + "archive/_Archive.html"],
    ];

    const nav = document.createElement("ul");
    nav.id = "pd-nav";

    for (const [label, href] of links) {
      const item = document.createElement("li");
      const link = document.createElement("a");
      link.href = href;
      link.textContent = label;
      item.appendChild(link);
      nav.appendChild(item);
    }

    menu.appendChild(nav);
  }

  const title = menu.querySelector(".menu-title");

  if (!title || title.matches("a")) {
    return;
  }

  const home = document.createElement("a");
  home.className = title.className;
  home.href = `${path_to_root}index.html`;
  home.setAttribute("aria-label", "PureDarwin home");
  home.title = "PureDarwin home";
  home.textContent = title.textContent;
  title.replaceWith(home);
});
