# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/simaopedro/Secretária/SETR/SETR/Trab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/simaopedro/Secretária/SETR/SETR/Trab1/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/dllLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/dllLib.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/dllLib.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/dllLib.dir/flags.make

lib/CMakeFiles/dllLib.dir/dll.c.o: lib/CMakeFiles/dllLib.dir/flags.make
lib/CMakeFiles/dllLib.dir/dll.c.o: /home/simaopedro/Secretária/SETR/SETR/Trab1/lib/dll.c
lib/CMakeFiles/dllLib.dir/dll.c.o: lib/CMakeFiles/dllLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/simaopedro/Secretária/SETR/SETR/Trab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/CMakeFiles/dllLib.dir/dll.c.o"
	cd /home/simaopedro/Secretária/SETR/SETR/Trab1/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lib/CMakeFiles/dllLib.dir/dll.c.o -MF CMakeFiles/dllLib.dir/dll.c.o.d -o CMakeFiles/dllLib.dir/dll.c.o -c /home/simaopedro/Secretária/SETR/SETR/Trab1/lib/dll.c

lib/CMakeFiles/dllLib.dir/dll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/dllLib.dir/dll.c.i"
	cd /home/simaopedro/Secretária/SETR/SETR/Trab1/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/simaopedro/Secretária/SETR/SETR/Trab1/lib/dll.c > CMakeFiles/dllLib.dir/dll.c.i

lib/CMakeFiles/dllLib.dir/dll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/dllLib.dir/dll.c.s"
	cd /home/simaopedro/Secretária/SETR/SETR/Trab1/build/lib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/simaopedro/Secretária/SETR/SETR/Trab1/lib/dll.c -o CMakeFiles/dllLib.dir/dll.c.s

# Object files for target dllLib
dllLib_OBJECTS = \
"CMakeFiles/dllLib.dir/dll.c.o"

# External object files for target dllLib
dllLib_EXTERNAL_OBJECTS =

lib/libdllLib.a: lib/CMakeFiles/dllLib.dir/dll.c.o
lib/libdllLib.a: lib/CMakeFiles/dllLib.dir/build.make
lib/libdllLib.a: lib/CMakeFiles/dllLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/simaopedro/Secretária/SETR/SETR/Trab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libdllLib.a"
	cd /home/simaopedro/Secretária/SETR/SETR/Trab1/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/dllLib.dir/cmake_clean_target.cmake
	cd /home/simaopedro/Secretária/SETR/SETR/Trab1/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dllLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/dllLib.dir/build: lib/libdllLib.a
.PHONY : lib/CMakeFiles/dllLib.dir/build

lib/CMakeFiles/dllLib.dir/clean:
	cd /home/simaopedro/Secretária/SETR/SETR/Trab1/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/dllLib.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/dllLib.dir/clean

lib/CMakeFiles/dllLib.dir/depend:
	cd /home/simaopedro/Secretária/SETR/SETR/Trab1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/simaopedro/Secretária/SETR/SETR/Trab1 /home/simaopedro/Secretária/SETR/SETR/Trab1/lib /home/simaopedro/Secretária/SETR/SETR/Trab1/build /home/simaopedro/Secretária/SETR/SETR/Trab1/build/lib /home/simaopedro/Secretária/SETR/SETR/Trab1/build/lib/CMakeFiles/dllLib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : lib/CMakeFiles/dllLib.dir/depend
