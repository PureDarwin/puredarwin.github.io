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

        nativeBuildInputs = [ pkgs.mdbook ];

        dontBuild = true;
        installPhase = ''
          runHook preInstall
          mdbook build --dest-dir "$out"
          runHook postInstall
        '';
      };

      serve = pkgs.writeShellApplication {
        name = "serve-puredarwin-docs";
        runtimeInputs = [ pkgs.mdbook ];
        text = ''
          exec mdbook serve \
            --hostname "''${MDBOOK_HOST:-127.0.0.1}" \
            --port "''${MDBOOK_PORT:-3000}" \
            "$@"
        '';
      };
    in {
      default = book;
      inherit book serve;
    });

    apps = forAllSystems (system: {
      default = self.apps.${system}.serve;
      serve = {
        type = "app";
        program = "${self.packages.${system}.serve}/bin/serve-puredarwin-docs";
      };
    });

    devShells = forAllSystems (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      default = pkgs.mkShellNoCC {
        packages = [ pkgs.mdbook ];
      };
    });
  };
}
