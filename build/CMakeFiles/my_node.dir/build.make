# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/ubuntu/node_program

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/node_program/build

# Include any dependencies generated for this target.
include CMakeFiles/my_node.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/my_node.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/my_node.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_node.dir/flags.make

CMakeFiles/my_node.dir/src/example.cc.o: CMakeFiles/my_node.dir/flags.make
CMakeFiles/my_node.dir/src/example.cc.o: ../src/example.cc
CMakeFiles/my_node.dir/src/example.cc.o: CMakeFiles/my_node.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/node_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_node.dir/src/example.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_node.dir/src/example.cc.o -MF CMakeFiles/my_node.dir/src/example.cc.o.d -o CMakeFiles/my_node.dir/src/example.cc.o -c /home/ubuntu/node_program/src/example.cc

CMakeFiles/my_node.dir/src/example.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_node.dir/src/example.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/node_program/src/example.cc > CMakeFiles/my_node.dir/src/example.cc.i

CMakeFiles/my_node.dir/src/example.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_node.dir/src/example.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/node_program/src/example.cc -o CMakeFiles/my_node.dir/src/example.cc.s

CMakeFiles/my_node.dir/src/main.cc.o: CMakeFiles/my_node.dir/flags.make
CMakeFiles/my_node.dir/src/main.cc.o: ../src/main.cc
CMakeFiles/my_node.dir/src/main.cc.o: CMakeFiles/my_node.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/node_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_node.dir/src/main.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_node.dir/src/main.cc.o -MF CMakeFiles/my_node.dir/src/main.cc.o.d -o CMakeFiles/my_node.dir/src/main.cc.o -c /home/ubuntu/node_program/src/main.cc

CMakeFiles/my_node.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_node.dir/src/main.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/node_program/src/main.cc > CMakeFiles/my_node.dir/src/main.cc.i

CMakeFiles/my_node.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_node.dir/src/main.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/node_program/src/main.cc -o CMakeFiles/my_node.dir/src/main.cc.s

# Object files for target my_node
my_node_OBJECTS = \
"CMakeFiles/my_node.dir/src/example.cc.o" \
"CMakeFiles/my_node.dir/src/main.cc.o"

# External object files for target my_node
my_node_EXTERNAL_OBJECTS =

my_node: CMakeFiles/my_node.dir/src/example.cc.o
my_node: CMakeFiles/my_node.dir/src/main.cc.o
my_node: CMakeFiles/my_node.dir/build.make
my_node: CMakeFiles/my_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/node_program/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable my_node"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_node.dir/build: my_node
.PHONY : CMakeFiles/my_node.dir/build

CMakeFiles/my_node.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_node.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_node.dir/clean

CMakeFiles/my_node.dir/depend:
	cd /home/ubuntu/node_program/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/node_program /home/ubuntu/node_program /home/ubuntu/node_program/build /home/ubuntu/node_program/build /home/ubuntu/node_program/build/CMakeFiles/my_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_node.dir/depend

