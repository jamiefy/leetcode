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
include CMakeFiles/lc10regularmatch.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lc10regularmatch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lc10regularmatch.dir/flags.make

CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.obj: CMakeFiles/lc10regularmatch.dir/flags.make
CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.obj: ../regularmatch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.obj"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\lc10regularmatch.dir\regularmatch.cpp.obj -c D:\leetcode\regularmatch.cpp

CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.i"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\leetcode\regularmatch.cpp > CMakeFiles\lc10regularmatch.dir\regularmatch.cpp.i

CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.s"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\leetcode\regularmatch.cpp -o CMakeFiles\lc10regularmatch.dir\regularmatch.cpp.s

CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.obj: CMakeFiles/lc10regularmatch.dir/flags.make
CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.obj: ../searchInsert.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.obj"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\lc10regularmatch.dir\searchInsert.cpp.obj -c D:\leetcode\searchInsert.cpp

CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.i"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\leetcode\searchInsert.cpp > CMakeFiles\lc10regularmatch.dir\searchInsert.cpp.i

CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.s"
	C:\qt\Qt5.12.0\Tools\mingw730_64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\leetcode\searchInsert.cpp -o CMakeFiles\lc10regularmatch.dir\searchInsert.cpp.s

# Object files for target lc10regularmatch
lc10regularmatch_OBJECTS = \
"CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.obj" \
"CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.obj"

# External object files for target lc10regularmatch
lc10regularmatch_EXTERNAL_OBJECTS =

lc10regularmatch.exe: CMakeFiles/lc10regularmatch.dir/regularmatch.cpp.obj
lc10regularmatch.exe: CMakeFiles/lc10regularmatch.dir/searchInsert.cpp.obj
lc10regularmatch.exe: CMakeFiles/lc10regularmatch.dir/build.make
lc10regularmatch.exe: CMakeFiles/lc10regularmatch.dir/linklibs.rsp
lc10regularmatch.exe: CMakeFiles/lc10regularmatch.dir/objects1.rsp
lc10regularmatch.exe: CMakeFiles/lc10regularmatch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable lc10regularmatch.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lc10regularmatch.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lc10regularmatch.dir/build: lc10regularmatch.exe

.PHONY : CMakeFiles/lc10regularmatch.dir/build

CMakeFiles/lc10regularmatch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lc10regularmatch.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lc10regularmatch.dir/clean

CMakeFiles/lc10regularmatch.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\leetcode D:\leetcode D:\leetcode\cmake-build-debug D:\leetcode\cmake-build-debug D:\leetcode\cmake-build-debug\CMakeFiles\lc10regularmatch.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lc10regularmatch.dir/depend

