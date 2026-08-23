document.addEventListener("DOMContentLoaded", () => {
  const menu = document.querySelector("#mdbook-menu-bar");

  if (!menu) {
    return;
  }

  // mdBook nests the masthead in its sidebar-shifted page wrapper. Moving the
  // same node preserves all built-in event handlers while anchoring it to the
  // viewport instead of the current sidebar width.
  document.body.appendChild(menu);

  // The stylesheet's --pd-scrollbar fallback assumes a 15px classic
  // scrollbar, but overlay scrollbars (macOS default) take no space, which
  // shifted this bar half that width relative to the landing page. Measure
  // what a scrollbar really occupies and correct the variable.
  const probe = document.createElement("div");
  probe.style.cssText =
    "position:absolute;top:-9999px;width:100px;height:100px;overflow:scroll;";
  document.body.appendChild(probe);
  document.documentElement.style.setProperty(
    "--pd-scrollbar",
    probe.offsetWidth - probe.clientWidth + "px",
  );
  probe.remove();

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
      toggle.title = "Switch to " + (dark ? "light" : "dark") + " theme";
      toggle.setAttribute("aria-label", toggle.title);
    };

    paint(isDark());

    // Click mdBook's own (hidden) entry rather than setting the class here:
    // it owns the stylesheet switching for the highlight themes, the stored
    // preference and the theme-color meta tag. Removing its picker from the
    // DOM would make all of that throw, which is how the code blocks ended up
    // with the dark highlight sheet in light mode.
    toggle.addEventListener("click", () => {
      const dark = !isDark();
      const target = document.getElementById(
        dark ? "mdbook-theme-navy" : "mdbook-theme-light",
      );
      if (target) {
        target.click();
      }
      paint(dark);
    });

    // Leftmost in the group, matching where the landing page puts it.
    const leftButtons = picker.closest(".left-buttons");
    if (leftButtons) {
      leftButtons.prepend(toggle);
    } else {
      picker.after(toggle);
    }
  }

  // Same links as the landing page, in the same corner, so moving between the
  // two halves of the site does not move the navigation.
  const root = typeof path_to_root === "string" ? path_to_root : "";
  const links = [
    ["Home", root + "index.html"],
    ["Handbook", root + "handbook/_Handbook.html"],
    ["News", root + "news/_News.html"],
    ["Get it", root + "index.html#get-it"],
    ["GitHub", "https://github.com/PureDarwin/PureDarwin"],
    ["Archive", root + "archive/_Archive.html"],
  ];

  const buildLinkList = (id) => {
    const nav = document.createElement("ul");
    nav.id = id;
    for (const [label, href] of links) {
      const item = document.createElement("li");
      const link = document.createElement("a");
      link.href = href;
      link.textContent = label;
      item.appendChild(link);
      nav.appendChild(item);
    }
    return nav;
  };

  if (!menu.querySelector("#pd-nav")) {
    menu.appendChild(buildLinkList("pd-nav"));
  }

  // Below 760px the inline links are hidden, so the same list moves into a
  // dropdown behind a hamburger. It matches the landing page's mobile menu.
  if (!document.querySelector("#pd-nav-toggle")) {
    const MENU_ICON =
      '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" ' +
      'stroke="currentColor" stroke-width="2" stroke-linecap="round" ' +
      'stroke-linejoin="round"><path d="M4 6h16"/><path d="M4 12h16"/>' +
      '<path d="M4 18h16"/></svg>';
    const CLOSE_ICON =
      '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" ' +
      'stroke="currentColor" stroke-width="2" stroke-linecap="round" ' +
      'stroke-linejoin="round"><path d="M18 6 6 18"/><path d="m6 6 12 12"/></svg>';

    const dropdown = buildLinkList("pd-mobile-nav");

    // On mobile the bar's theme toggle is hidden; the same control lives at
    // the foot of this menu instead, as on the landing page. Clicking relays
    // to the (hidden) bar toggle so the switching logic stays in one place.
    const headerToggle = document.querySelector("#pd-theme-toggle");
    if (headerToggle) {
      const themeItem = document.createElement("li");
      themeItem.className = "pd-mobile-theme-item";
      const themeButton = document.createElement("button");
      themeButton.type = "button";
      themeButton.id = "pd-mobile-theme";

      const paintMobileTheme = () => {
        const dark = !document.documentElement.classList.contains("light");
        themeButton.innerHTML =
          '<span class="fa-svg">' +
          (dark ? SUN : MOON) +
          "</span>" +
          (dark ? "Light mode" : "Dark mode");
      };

      paintMobileTheme();

      themeButton.addEventListener("click", () => {
        headerToggle.click();
        paintMobileTheme();
      });

      themeItem.appendChild(themeButton);
      dropdown.appendChild(themeItem);
    }

    document.body.appendChild(dropdown);

    const navToggle = document.createElement("button");
    navToggle.type = "button";
    navToggle.id = "pd-nav-toggle";
    navToggle.className = "icon-button";
    navToggle.setAttribute("aria-expanded", "false");
    navToggle.setAttribute("aria-controls", "pd-mobile-nav");

    const paintNav = (open) => {
      navToggle.innerHTML =
        '<span class="fa-svg">' + (open ? CLOSE_ICON : MENU_ICON) + "</span>";
      navToggle.title = (open ? "Close" : "Open") + " navigation menu";
      navToggle.setAttribute("aria-label", navToggle.title);
      navToggle.setAttribute("aria-expanded", open ? "true" : "false");
    };

    paintNav(false);

    navToggle.addEventListener("click", () => {
      paintNav(dropdown.classList.toggle("open"));
    });

    dropdown.addEventListener("click", (e) => {
      if (e.target.closest("a")) {
        dropdown.classList.remove("open");
        paintNav(false);
      }
    });

    const rightButtons = menu.querySelector(".right-buttons");
    (rightButtons || menu).appendChild(navToggle);
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
