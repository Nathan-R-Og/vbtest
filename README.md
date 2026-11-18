# VBTest
Test homebrew for Virtual Boy

id use `VUCC` but this is so much easier

Currently only works on Linux Ubuntu. Could probably work on Windows, I'm just lazy.

## Using
This project uses [v810-gcc](https://github.com/jbrandwood/v810-gcc) to compile, assemble and link. This project also uses the `ninja` build system.

1. Install `v810-gcc` and other dependencies by running `./install`. This will install `v810-gcc` at `tools/v810-gcc` as well as otehr python dependencies.

2. Run `./configure` to set up a ninja build script.

3. Run `ninja` to compile the project.

The output will be at `build/vbtest.vb`.


## Project Directory:
`src/` - All source code files.

`include/` - All source code header files.

`build/` - Build output.

`tools/` - Extraneous tools for development.


