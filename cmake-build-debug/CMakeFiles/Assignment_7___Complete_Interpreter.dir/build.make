# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/hamon11/Downloads/clion-2017.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/hamon11/Downloads/clion-2017.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Assignment_7___Complete_Interpreter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Assignment_7___Complete_Interpreter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assignment_7___Complete_Interpreter.dir/flags.make

CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o: CMakeFiles/Assignment_7___Complete_Interpreter.dir/flags.make
CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o: ../Interpreter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o   -c "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/Interpreter.c"

CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/Interpreter.c" > CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.i

CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/Interpreter.c" -o CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.s

CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o.requires:

.PHONY : CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o.requires

CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o.provides: CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o.requires
	$(MAKE) -f CMakeFiles/Assignment_7___Complete_Interpreter.dir/build.make CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o.provides.build
.PHONY : CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o.provides

CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o.provides.build: CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o


# Object files for target Assignment_7___Complete_Interpreter
Assignment_7___Complete_Interpreter_OBJECTS = \
"CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o"

# External object files for target Assignment_7___Complete_Interpreter
Assignment_7___Complete_Interpreter_EXTERNAL_OBJECTS =

Assignment_7___Complete_Interpreter: CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o
Assignment_7___Complete_Interpreter: CMakeFiles/Assignment_7___Complete_Interpreter.dir/build.make
Assignment_7___Complete_Interpreter: CMakeFiles/Assignment_7___Complete_Interpreter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Assignment_7___Complete_Interpreter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Assignment_7___Complete_Interpreter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assignment_7___Complete_Interpreter.dir/build: Assignment_7___Complete_Interpreter

.PHONY : CMakeFiles/Assignment_7___Complete_Interpreter.dir/build

CMakeFiles/Assignment_7___Complete_Interpreter.dir/requires: CMakeFiles/Assignment_7___Complete_Interpreter.dir/Interpreter.c.o.requires

.PHONY : CMakeFiles/Assignment_7___Complete_Interpreter.dir/requires

CMakeFiles/Assignment_7___Complete_Interpreter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Assignment_7___Complete_Interpreter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Assignment_7___Complete_Interpreter.dir/clean

CMakeFiles/Assignment_7___Complete_Interpreter.dir/depend:
	cd "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter" "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter" "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/cmake-build-debug" "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/cmake-build-debug" "/home/hamon11/OneDrive/School/YU/Classes/2017 Fall/Programming Languages/Assignments/Assignment 7 - Complete Interpreter/cmake-build-debug/CMakeFiles/Assignment_7___Complete_Interpreter.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Assignment_7___Complete_Interpreter.dir/depend

