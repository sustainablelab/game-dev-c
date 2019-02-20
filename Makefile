test-output := build/TestSuite-results.md
# =====[ Default Target ]=====
unit-test: ${test-output}

unittest-framework-path := /home/Mike/c/tdd/unity/

# pkg-config returns compiler flags and linker libs and flags
# Cygwin pkg-config: just call pkg-config (this is /usr/bin/pkg-config.exe)
# Windows pkg-config: /usr/bin/x86_64-w64-mingw32-pkg-config.exe
# =====[ Compiler flags ]=====
CFLAGS_for_cygwin := -I${unittest-framework-path} \
	-Itest -Isrc \
	-D_REENTRANT -I/usr/include/SDL2 \
	-g -Wall -Wextra -pedantic
CFLAGS_for_windows := -I${unittest-framework-path} \
	-Itest -Isrc \
	-Dmain=SDL_main -I/usr/x86_64-w64-mingw32/sys-root/mingw/include/SDL2 \
	-g -Wall -Wextra -pedantic
# cygwin compilers are the short names
# mingw compilers have huge prefixed names
ifeq ($(compiler),gcc)
	CFLAGS := $(CFLAGS_for_cygwin)
endif
ifeq ($(compiler),clang)
	CFLAGS := $(CFLAGS_for_cygwin)
endif
ifeq ($(compiler),g++)
	CFLAGS := $(CFLAGS_for_cygwin)
endif
ifeq ($(compiler),x86_64-w64-mingw32-gcc)
	CFLAGS := $(CFLAGS_for_windows)
endif

LFLAGS_for_cygwin := -lSDL2
LFLAGS_for_windows := -lmingw32 -lSDL2main -lSDL2 \
	 -mwindows -Wl,--no-undefined \
	 -lm -liconv -ldinput8 -ldxguid -ldxerr8 -luser32 \
	 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion \
	 /lib/w32api/libuuid.a -static-libgcc
ifeq ($(compiler),gcc)
	LFLAGS := $(LFLAGS_for_cygwin)
endif
ifeq ($(compiler),clang)
	LFLAGS := $(LFLAGS_for_cygwin)
endif
ifeq ($(compiler),g++)
	LFLAGS := $(LFLAGS_for_cygwin)
endif
ifeq ($(compiler),x86_64-w64-mingw32-gcc)
	LFLAGS := $(LFLAGS_for_windows)
endif

unittest-framework-obj := build/unity.o
# =====[ Compile the unittest framework object file ]=====
${unittest-framework-obj}: ${unittest-framework-path}unity.c
	${compiler} -c $^ -o $@ $(CFLAGS)

names-of-test-files := test_HasWindow test_HasVersion
test-objects := $(addsuffix .o,${names-of-test-files})
test-objects := $(addprefix build/,${test-objects})
#=====[ Explicit rule for test objects ]=====
${test-objects}: build/%.o: test/%.c
	${compiler} -c $^ -o $@ $(CFLAGS)


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

# =====[ Run test suite and save test results in markdown file ]=====
${test-output}: build/TestSuite.exe
	$^ > $@

test-runner := test/test_runner.c
# =====[ Recipe to build the test suite. ]=====
build/TestSuite.exe: ${test-runner} ${test-objects} ${unittest-framework-obj}
	${compiler} $^ -o $@ $(LFLAGS) $(CFLAGS)

.PHONY: clean-TestSuite clean-all-builds
clean-TestSuite:
	rm -f build/TestSuite.exe

clean-all-builds:
	rm -f build/TestSuite.exe
	rm -f build/TestSuite-results.md
	rm -f build/TestSuite-results.html
	rm -f build/*.o
	rm -f build/*.asm
