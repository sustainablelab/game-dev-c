% Build `game-dev`

# Build `TestSuite.exe` from `test_runner.c`
The build runs the `.exe` and outputs the test results markdown file.

## Cygwin
Builds for Cygwin require an X11 XServer and windows manager on Port 0:0 to run
the executable.

For cygwin with gcc:
```vim
;mkgc
```

For cygwin with g++:
```vim
;mkg+
```

For cygwin with clang
```vim
;mkcl
```

For cygwin with clang++:
```vim
;mkc+
```

## Native Windows

For mingw with gcc:
```vim
;mkwgc
```

For mingw with g++:
```vim
;mkwg+
```

For mingw with clang
```vim
;mkwcl
```

For mingw with clang++:
```vim
;mkwc+
```

# Display Test Results in Vim
This also runs the `.exe` but it has the additional step of opening a window in
Vim to display the test results.

Just replace the `k` in all the shortcuts with `t`.

This is my traditional route. The alternative with `k` is to then `pandoc` the
test results to an `html` file and refresh the view in Chrome.

- [ ] fix the output from the Unity C unit test framework to be markdown
  friendly by eliminating the underscores from the test names


