Required for the install in the .emacs.d folder:
- `atom-one-dark-theme`: https://github.com/jonathanchu/atom-one-dark-theme/blob/master/atom-one-dark-theme.el
- `.clang-format`: https://github.com/mark182182/sandbox/blob/master/.clang-format
- `clang-format.el`: https://github.com/llvm/llvm-project/blob/main/clang/tools/clang-format/clang-format.el

Custom Emacs (evil-mode) stuff:
- `:Ctr-v` -> vertically select
- `:yy` -> copy selected
- `:%s/foo/bar` -> replace 'foo' with 'bar' in all occurances (can be combined with selection)
- `:new` -> create new buffer
- `:w [filename]` -> save file to current directory
- `:C-x h` -> select all lines
- `grep RET` -> run grep like so: grep -nH "window" *.h
- `<f8>` -> search for files
- `<f8>` navigate to the file and press alt+shift+r -> rename selected file
- `<f9>` -> clang format
- `:vsplit` -> create vertical tab
- `:C-w w` -> switch tabs
- `:v i s` -> select current block
- `:g v` -> reselect previous selection
- `:M-g g` -> jump to line by number
- `:Altgr ;` -> toggle comment block
