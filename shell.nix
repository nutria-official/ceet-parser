{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    clang
    gcc
    gdb
  ];

  shellHook = ''
    echo "C-shell loaded."
  '';
}
