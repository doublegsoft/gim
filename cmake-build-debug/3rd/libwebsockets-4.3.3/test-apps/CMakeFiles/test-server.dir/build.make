# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug

# Include any dependencies generated for this target.
include 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/depend.make

# Include the progress variables for this target.
include 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/progress.make

# Include the compile flags for this target's objects.
include 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/flags.make

3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/test-server.c.o: 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/flags.make
3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/test-server.c.o: ../3rd/libwebsockets-4.3.3/test-apps/test-server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/test-server.c.o"
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test-server.dir/test-server.c.o   -c /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test-server.c

3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/test-server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test-server.dir/test-server.c.i"
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test-server.c > CMakeFiles/test-server.dir/test-server.c.i

3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/test-server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test-server.dir/test-server.c.s"
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test-server.c -o CMakeFiles/test-server.dir/test-server.c.s

# Object files for target test-server
test__server_OBJECTS = \
"CMakeFiles/test-server.dir/test-server.c.o"

# External object files for target test-server
test__server_EXTERNAL_OBJECTS =

3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server: 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/test-server.c.o
3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server: 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/build.make
3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server: 3rd/libwebsockets-4.3.3/lib/libwebsockets.a
3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server: /usr/local/Cellar/openssl@3/3.1.3/lib/libssl.dylib
3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server: /usr/local/Cellar/openssl@3/3.1.3/lib/libcrypto.dylib
3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server: /usr/local/Cellar/openssl@3/3.1.3/lib/libssl.dylib
3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server: /usr/local/Cellar/openssl@3/3.1.3/lib/libcrypto.dylib
3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server: 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/libwebsockets-test-server"
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-server.dir/link.txt --verbose=$(VERBOSE)
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E make_directory /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/libwebsockets-test-server.key.pem /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/libwebsockets-test-server.pem /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/favicon.ico /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/leaf.jpg /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/candide.zip /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/candide-uncompressed.zip /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/libwebsockets.org-logo.svg /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/http2.png /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/wss-over-h2.png /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/lws-common.js /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test.html /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test.css /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E copy /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test.js /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/../share/libwebsockets-test-server

# Rule to build all files generated by this target.
3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/build: 3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server

.PHONY : 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/build

3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/clean:
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps && $(CMAKE_COMMAND) -P CMakeFiles/test-server.dir/cmake_clean.cmake
.PHONY : 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/clean

3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/depend:
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3rd/libwebsockets-4.3.3/test-apps/CMakeFiles/test-server.dir/depend

