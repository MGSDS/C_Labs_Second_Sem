# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = "/Users/bwilliams/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/203.7717.62/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/bwilliams/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/203.7717.62/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/FourthLab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FourthLab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FourthLab.dir/flags.make

CMakeFiles/FourthLab.dir/main.cpp.o: CMakeFiles/FourthLab.dir/flags.make
CMakeFiles/FourthLab.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FourthLab.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FourthLab.dir/main.cpp.o -c /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/main.cpp

CMakeFiles/FourthLab.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FourthLab.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/main.cpp > CMakeFiles/FourthLab.dir/main.cpp.i

CMakeFiles/FourthLab.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FourthLab.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/main.cpp -o CMakeFiles/FourthLab.dir/main.cpp.s

# Object files for target FourthLab
FourthLab_OBJECTS = \
"CMakeFiles/FourthLab.dir/main.cpp.o"

# External object files for target FourthLab
FourthLab_EXTERNAL_OBJECTS =

FourthLab: CMakeFiles/FourthLab.dir/main.cpp.o
FourthLab: CMakeFiles/FourthLab.dir/build.make
FourthLab: CMakeFiles/FourthLab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FourthLab"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FourthLab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FourthLab.dir/build: FourthLab

.PHONY : CMakeFiles/FourthLab.dir/build

CMakeFiles/FourthLab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FourthLab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FourthLab.dir/clean

CMakeFiles/FourthLab.dir/depend:
	cd /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/cmake-build-debug /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/cmake-build-debug /Users/bwilliams/Documents/C-Labs-Second-Semester/FourthLab/cmake-build-debug/CMakeFiles/FourthLab.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FourthLab.dir/depend

