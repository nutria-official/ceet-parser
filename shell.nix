{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    clang
  ];

  shellHook = ''
    echo "C-shell loaded."
  '';
}
