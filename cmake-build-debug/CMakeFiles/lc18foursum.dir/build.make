# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\leetcode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\leetcode\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lc18foursum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lc18foursum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lc18foursum.dir/flags.make

CMakeFiles/lc18foursum.dir/foursum.cpp.obj: CMakeFiles/lc18foursum.dir/flags.make
CMakeFiles/lc18foursum.dir/foursum.cpp.obj: ../foursum.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lc18foursum.dir/foursum.cpp.obj"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\lc18foursum.dir\foursum.cpp.obj -c D:\leetcode\foursum.cpp

CMakeFiles/lc18foursum.dir/foursum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lc18foursum.dir/foursum.cpp.i"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\leetcode\foursum.cpp > CMakeFiles\lc18foursum.dir\foursum.cpp.i

CMakeFiles/lc18foursum.dir/foursum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lc18foursum.dir/foursum.cpp.s"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\leetcode\foursum.cpp -o CMakeFiles\lc18foursum.dir\foursum.cpp.s

# Object files for target lc18foursum
lc18foursum_OBJECTS = \
"CMakeFiles/lc18foursum.dir/foursum.cpp.obj"

# External object files for target lc18foursum
lc18foursum_EXTERNAL_OBJECTS =

lc18foursum.exe: CMakeFiles/lc18foursum.dir/foursum.cpp.obj
lc18foursum.exe: CMakeFiles/lc18foursum.dir/build.make
lc18foursum.exe: CMakeFiles/lc18foursum.dir/linklibs.rsp
lc18foursum.exe: CMakeFiles/lc18foursum.dir/objects1.rsp
lc18foursum.exe: CMakeFiles/lc18foursum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lc18foursum.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lc18foursum.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lc18foursum.dir/build: lc18foursum.exe

.PHONY : CMakeFiles/lc18foursum.dir/build

CMakeFiles/lc18foursum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lc18foursum.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lc18foursum.dir/clean

CMakeFiles/lc18foursum.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\leetcode D:\leetcode D:\leetcode\cmake-build-debug D:\leetcode\cmake-build-debug D:\leetcode\cmake-build-debug\CMakeFiles\lc18foursum.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lc18foursum.dir/depend

