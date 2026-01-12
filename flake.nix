{
  description = "Project dependencies and tools";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem
    (
      system: let
        pkgs = import nixpkgs;
      in
        with pkgs; {
          devShells.default = mkShell {
            nativeBuildInputs = with pkgs; [
              git
              cmake

              # Lsp
              nixd
              clang-tools
              cmake-language-server

              # Profiling
              hotspot
              perf
            ];
            buildInputs = [];
          };
        }
    );
}
