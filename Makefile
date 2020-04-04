game := boss-typing
game_output := build/$(game)
game_src := src/$(game)
test_output := build/TestSuite-results
# =====[ Default Target ]=====
play-game: $(game_output).exe
view-tests-in-Chrome: ${test_output}.html
view-tests-in-Vim: ${test_output}.md

unittest_framework_path := /home/Mike/c/tdd/unity/

# pkg-config returns compiler flags and linker libs and flags
# Cygwin pkg-config: just call pkg-config (this is /usr/bin/pkg-config.exe)
# Windows pkg-config: /usr/bin/x86_64-w64-mingw32-pkg-config.exe
# =====[ Compiler flags ]=====
CFLAGS_for_cygwin := -I${unittest_framework_path} \
	-Itest -Isrc \
	-D_REENTRANT -I/usr/include/SDL2 \
	-g -Wall -Wextra -pedantic
CFLAGS_for_windows := -I${unittest_framework_path} \
	-Itest -Isrc \
	-Dmain=SDL_main \
	-DUNITY_LONG_WIDTH=64 \
	-I/usr/x86_64-w64-mingw32/sys-root/mingw/include/SDL2 \
	-g -Wall -Wextra -pedantic
# =====[ Linker libs and flags ]=====
LFLAGS_for_cygwin := -lSDL2
LFLAGS_for_windows := -lmingw32 -lSDL2main -lSDL2 \
	 -mwindows -Wl,--no-undefined \
	 -lm -liconv -ldinput8 -ldxguid -ldxerr8 -luser32 \
	 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion \
	 /lib/w32api/libuuid.a -static-libgcc
# cygwin compilers are the short names
ifeq ($(compiler),gcc)
	CFLAGS := $(CFLAGS_for_cygwin)
	LFLAGS := $(LFLAGS_for_cygwin)
endif
ifeq ($(compiler),clang)
	CFLAGS := $(CFLAGS_for_cygwin)
	LFLAGS := $(LFLAGS_for_cygwin)
endif
ifeq ($(compiler),g++)
	CFLAGS := $(CFLAGS_for_cygwin) -x c++
	LFLAGS := $(LFLAGS_for_cygwin)
endif
ifeq ($(compiler),clang++)
	CFLAGS := $(CFLAGS_for_cygwin) -x c++
	LFLAGS := $(LFLAGS_for_cygwin)
endif
# mingw compilers have huge prefixed names
ifeq ($(compiler),x86_64-w64-mingw32-gcc)
	CFLAGS := $(CFLAGS_for_windows)
	LFLAGS := $(LFLAGS_for_windows)
endif
ifeq ($(compiler),x86_64-w64-mingw32-g++)
	CFLAGS := $(CFLAGS_for_windows) -x c++
	LFLAGS := $(LFLAGS_for_windows)
endif
ifeq ($(compiler),x86_64-w64-mingw32-clang)
	CFLAGS := $(CFLAGS_for_windows)
	LFLAGS := $(LFLAGS_for_windows)
endif
ifeq ($(compiler),x86_64-w64-mingw32-clang++)
	CFLAGS := $(CFLAGS_for_windows) -x c++
	LFLAGS := $(LFLAGS_for_windows)
endif

unittest_framework_obj := build/unity.o
# =====[ Compile the unittest framework object file ]=====
${unittest_framework_obj}: ${unittest_framework_path}unity.c
	${compiler} $(CFLAGS) -c $^ -o $@

names-of-test-files := test_runner test_HasWindow test_HasVersion
test_objects := $(addsuffix .o,${names-of-test-files})
test_objects := $(addprefix build/,${test_objects})
#=====[ Explicit rule for test objects ]=====
${test_objects}: build/%.o: test/%.c
	${compiler} $(CFLAGS) -c $^ -o $@


# =====[ Make file `lib-dependencies` for `ctags` ]=====
# Make a list of header files using `gcc`. Then format the list with `sed`.
# 	s/pat-old/pat-new/g is global substitution
# 	/^ /d deletes all lines starting with a blank space
# 	/^ *$/d deletes all blank lines or lines with spaces only
# 	Note the use of $$ to escape the '$' in `make`
# 	/\.o:/d deletes all lines containing search pattern '.o:'
# 	/\.c$$/d deletes all lines ending in pattern '.c'
lib-dependencies: lib-dependencies.c
	${compiler} -M $^ $(CFLAGS) | sed -e 's/[\\ ]/\n/g' | \
		sed -e '/^ *$$/d' | \
		sed -e '/\.o:/d'  | \
		sed -e '/\.c$$/d' \
		> $@

# =====[ Build game output ]=====
$(game_output).o: $(game_src).c
	${compiler} $(CFLAGS) -c $^ -o $@

$(game_output).exe: $(game_output).o
	${compiler} $^ -o $@ $(LFLAGS)

# =====[ Run test suite and save test results in markdown file ]=====
${test_output}.md: build/TestSuite.exe
	$^ > $@

${test_output}.html: ${test_output}.md
	pandoc -f markdown $^ -s -o $@ -c pandoc.css --toc

# =====[ Recipe to build the test suite. Just linking object files. ]=====
build/TestSuite.exe: ${test_objects} ${unittest_framework_obj}
	${compiler} $^ -o $@ $(LFLAGS)

.PHONY: clean-TestSuite clean-all-builds
clean-TestSuite:
	rm -f build/TestSuite.exe

clean-all-builds:
	rm -f build/TestSuite.exe
	rm -f build/TestSuite-results.md
	rm -f build/TestSuite-results.html
	rm -f build/*.o
	rm -f build/*.asm
