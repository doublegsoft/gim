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
include CMakeFiles/gim_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gim_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gim_client.dir/flags.make

CMakeFiles/gim_client.dir/test/gim_client.c.o: CMakeFiles/gim_client.dir/flags.make
CMakeFiles/gim_client.dir/test/gim_client.c.o: ../test/gim_client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gim_client.dir/test/gim_client.c.o"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gim_client.dir/test/gim_client.c.o   -c /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/test/gim_client.c

CMakeFiles/gim_client.dir/test/gim_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gim_client.dir/test/gim_client.c.i"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/test/gim_client.c > CMakeFiles/gim_client.dir/test/gim_client.c.i

CMakeFiles/gim_client.dir/test/gim_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gim_client.dir/test/gim_client.c.s"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/test/gim_client.c -o CMakeFiles/gim_client.dir/test/gim_client.c.s

CMakeFiles/gim_client.dir/test/toyws.c.o: CMakeFiles/gim_client.dir/flags.make
CMakeFiles/gim_client.dir/test/toyws.c.o: ../test/toyws.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gim_client.dir/test/toyws.c.o"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gim_client.dir/test/toyws.c.o   -c /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/test/toyws.c

CMakeFiles/gim_client.dir/test/toyws.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gim_client.dir/test/toyws.c.i"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/test/toyws.c > CMakeFiles/gim_client.dir/test/toyws.c.i

CMakeFiles/gim_client.dir/test/toyws.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gim_client.dir/test/toyws.c.s"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/test/toyws.c -o CMakeFiles/gim_client.dir/test/toyws.c.s

CMakeFiles/gim_client.dir/src/gim-util.c.o: CMakeFiles/gim_client.dir/flags.make
CMakeFiles/gim_client.dir/src/gim-util.c.o: ../src/gim-util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/gim_client.dir/src/gim-util.c.o"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gim_client.dir/src/gim-util.c.o   -c /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/src/gim-util.c

CMakeFiles/gim_client.dir/src/gim-util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gim_client.dir/src/gim-util.c.i"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/src/gim-util.c > CMakeFiles/gim_client.dir/src/gim-util.c.i

CMakeFiles/gim_client.dir/src/gim-util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gim_client.dir/src/gim-util.c.s"
	/opt/local/bin/x86_64-w64-mingw32-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/src/gim-util.c -o CMakeFiles/gim_client.dir/src/gim-util.c.s

# Object files for target gim_client
gim_client_OBJECTS = \
"CMakeFiles/gim_client.dir/test/gim_client.c.o" \
"CMakeFiles/gim_client.dir/test/toyws.c.o" \
"CMakeFiles/gim_client.dir/src/gim-util.c.o"

# External object files for target gim_client
gim_client_EXTERNAL_OBJECTS =

gim_client: CMakeFiles/gim_client.dir/test/gim_client.c.o
gim_client: CMakeFiles/gim_client.dir/test/toyws.c.o
gim_client: CMakeFiles/gim_client.dir/src/gim-util.c.o
gim_client: CMakeFiles/gim_client.dir/build.make
gim_client: 3rd/json-c-json-c-0.16-20220414/libjson-c.5.2.0.dylib
gim_client: CMakeFiles/gim_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable gim_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gim_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gim_client.dir/build: gim_client

.PHONY : CMakeFiles/gim_client.dir/build

CMakeFiles/gim_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gim_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gim_client.dir/clean

CMakeFiles/gim_client.dir/depend:
	cd /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/CMakeFiles/gim_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gim_client.dir/depend

