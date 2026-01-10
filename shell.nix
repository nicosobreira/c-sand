{pkgs ? import <nixpkgs> {}}: let
  raylib_5_5 = pkgs.raylib.overrideAttrs (old: {
    version = "5.5";

    src = pkgs.fetchFromGitHub {
      owner = "raysan5";
      repo = "raylib";
      rev = "5.5";
      sha256 = "sha256-J99i4z4JF7d6mJNuJIB0rHNDhXJ5AEkG0eBvvuBLHrY=";
    };
  });
in
  pkgs.mkShell {
    strictDeps = true;
    # Tools
    nativeBuildInputs = with pkgs; [
      clang-tools
      cmake-language-server
      cmake

      hotspot
      perf
    ];

    # Libraries
    buildInputs = with pkgs; [
      raylib_5_5
    ];
  }
