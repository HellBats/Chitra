# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/hellbats/Code/Chitra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hellbats/Code/Chitra/build

# Include any dependencies generated for this target.
include CMakeFiles/buld.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/buld.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/buld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/buld.dir/flags.make

CMakeFiles/buld.dir/src/example.c.o: CMakeFiles/buld.dir/flags.make
CMakeFiles/buld.dir/src/example.c.o: /home/hellbats/Code/Chitra/src/example.c
CMakeFiles/buld.dir/src/example.c.o: CMakeFiles/buld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hellbats/Code/Chitra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/buld.dir/src/example.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/buld.dir/src/example.c.o -MF CMakeFiles/buld.dir/src/example.c.o.d -o CMakeFiles/buld.dir/src/example.c.o -c /home/hellbats/Code/Chitra/src/example.c

CMakeFiles/buld.dir/src/example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/buld.dir/src/example.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hellbats/Code/Chitra/src/example.c > CMakeFiles/buld.dir/src/example.c.i

CMakeFiles/buld.dir/src/example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/buld.dir/src/example.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hellbats/Code/Chitra/src/example.c -o CMakeFiles/buld.dir/src/example.c.s

# Object files for target buld
buld_OBJECTS = \
"CMakeFiles/buld.dir/src/example.c.o"

# External object files for target buld
buld_EXTERNAL_OBJECTS =

buld: CMakeFiles/buld.dir/src/example.c.o
buld: CMakeFiles/buld.dir/build.make
buld: CMakeFiles/buld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hellbats/Code/Chitra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable buld"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/buld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/buld.dir/build: buld
.PHONY : CMakeFiles/buld.dir/build

CMakeFiles/buld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/buld.dir/cmake_clean.cmake
.PHONY : CMakeFiles/buld.dir/clean

CMakeFiles/buld.dir/depend:
	cd /home/hellbats/Code/Chitra/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hellbats/Code/Chitra /home/hellbats/Code/Chitra /home/hellbats/Code/Chitra/build /home/hellbats/Code/Chitra/build /home/hellbats/Code/Chitra/build/CMakeFiles/buld.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/buld.dir/depend

