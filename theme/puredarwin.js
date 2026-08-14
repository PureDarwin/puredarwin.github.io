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
