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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project_10a.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project_10a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project_10a.dir/flags.make

CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.o: CMakeFiles/project_10a.dir/flags.make
CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.o: ../hw10_task_A_graphs_connected_components.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.o -c /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/hw10_task_A_graphs_connected_components.cpp

CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/hw10_task_A_graphs_connected_components.cpp > CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.i

CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/hw10_task_A_graphs_connected_components.cpp -o CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.s

# Object files for target project_10a
project_10a_OBJECTS = \
"CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.o"

# External object files for target project_10a
project_10a_EXTERNAL_OBJECTS =

project_10a: CMakeFiles/project_10a.dir/hw10_task_A_graphs_connected_components.cpp.o
project_10a: CMakeFiles/project_10a.dir/build.make
project_10a: CMakeFiles/project_10a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable project_10a"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project_10a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project_10a.dir/build: project_10a

.PHONY : CMakeFiles/project_10a.dir/build

CMakeFiles/project_10a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project_10a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project_10a.dir/clean

CMakeFiles/project_10a.dir/depend:
	cd /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2 /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2 /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/cmake-build-debug /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/cmake-build-debug /Users/annabeketova/Yandex.Disk.localized/MADE2020/Algo/project2/cmake-build-debug/CMakeFiles/project_10a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project_10a.dir/depend

