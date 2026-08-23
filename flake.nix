{
  description = "PureDarwin documentation";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }: let
    systems = [
      "x86_64-linux"
      "aarch64-linux"
      "x86_64-darwin"
      "aarch64-darwin"
    ];
    forAllSystems = nixpkgs.lib.genAttrs systems;
  in {
    packages = forAllSystems (system: let
      pkgs = nixpkgs.legacyPackages.${system};

      book = pkgs.stdenvNoCC.mkDerivation {
        pname = "puredarwin-docs";
        version = "0-unstable";
        src = self;

        nativeBuildInputs = [ pkgs.mdbook pkgs.tailwindcss_4 ];

        # The landing page (src/index.html) is Tailwind; the handbook is mdBook
        # plus theme/puredarwin.css. Tailwind runs first and writes into src/,
        # which mdBook then copies out along with the other static files.
        buildPhase = ''
          runHook preBuild
          tailwindcss \
            --input tailwind.css \
            --output src/css/site.css \
            --minify
          runHook postBuild
        '';

        installPhase = ''
          runHook preInstall
          mdbook build --dest-dir "$out"
          # GitHub Pages reads the custom domain from a CNAME in the published
          # artifact. It lives at the repository root, which mdBook does not
          # copy, so put it in the output here rather than in the workflow.
          # Optional, so a fork can simply delete it and still build.
          if [ -e CNAME ]; then
            cp CNAME "$out/CNAME"
          fi
          runHook postInstall
        '';
      };

      pdnews = pkgs.stdenv.mkDerivation {
        pname = "pdnews";
        version = "1.0.0";
        src = ./tools/pdnews;

        nativeBuildInputs = [ pkgs.cmake ];

        meta = {
          description = "List and create PureDarwin news entries";
          mainProgram = "pdnews";
        };
      };

      serve = pkgs.writeShellApplication {
        name = "serve-puredarwin-docs";
        runtimeInputs = [ pkgs.mdbook pkgs.tailwindcss_4 ];
        text = ''
          # Tailwind has to keep up with edits to index.html, otherwise mdBook
          # live-reloads against a stale stylesheet and the landing page
          # renders with whatever classes existed last time.
          tailwindcss \
            --input tailwind.css \
            --output src/css/site.css \
            --watch=always &
          tailwind_pid=$!
          trap 'kill "$tailwind_pid" 2>/dev/null || true' EXIT

          mdbook serve \
            --hostname "''${MDBOOK_HOST:-127.0.0.1}" \
            --port "''${MDBOOK_PORT:-3000}" \
            "$@"
        '';
      };

    in {
      default = book;
      inherit book serve pdnews;
    });

    apps = forAllSystems (system: {
      default = self.apps.${system}.serve;
      serve = {
        type = "app";
        program = "${self.packages.${system}.serve}/bin/serve-puredarwin-docs";
      };
      pdnews = {
        type = "app";
        program = "${self.packages.${system}.pdnews}/bin/pdnews";
      };
    });

    devShells = forAllSystems (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      default = pkgs.mkShell {
        packages = [
          pkgs.mdbook
          pkgs.tailwindcss_4
          pkgs.cmake
          self.packages.${system}.pdnews
        ];
      };
    });
  };
}
