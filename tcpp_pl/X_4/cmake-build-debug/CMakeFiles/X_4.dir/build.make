# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_SOURCE_DIR = /Users/jhilario/Documents/portfolio/tcpp_pl/X_4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/X_4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/X_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/X_4.dir/flags.make

CMakeFiles/X_4.dir/main.cpp.o: CMakeFiles/X_4.dir/flags.make
CMakeFiles/X_4.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jhilario/Documents/portfolio/tcpp_pl/X_4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/X_4.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/X_4.dir/main.cpp.o -c /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/main.cpp

CMakeFiles/X_4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/X_4.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/main.cpp > CMakeFiles/X_4.dir/main.cpp.i

CMakeFiles/X_4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/X_4.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/main.cpp -o CMakeFiles/X_4.dir/main.cpp.s

CMakeFiles/X_4.dir/general.cpp.o: CMakeFiles/X_4.dir/flags.make
CMakeFiles/X_4.dir/general.cpp.o: ../general.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jhilario/Documents/portfolio/tcpp_pl/X_4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/X_4.dir/general.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/X_4.dir/general.cpp.o -c /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/general.cpp

CMakeFiles/X_4.dir/general.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/X_4.dir/general.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/general.cpp > CMakeFiles/X_4.dir/general.cpp.i

CMakeFiles/X_4.dir/general.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/X_4.dir/general.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/general.cpp -o CMakeFiles/X_4.dir/general.cpp.s

# Object files for target X_4
X_4_OBJECTS = \
"CMakeFiles/X_4.dir/main.cpp.o" \
"CMakeFiles/X_4.dir/general.cpp.o"

# External object files for target X_4
X_4_EXTERNAL_OBJECTS =

X_4: CMakeFiles/X_4.dir/main.cpp.o
X_4: CMakeFiles/X_4.dir/general.cpp.o
X_4: CMakeFiles/X_4.dir/build.make
X_4: CMakeFiles/X_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jhilario/Documents/portfolio/tcpp_pl/X_4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable X_4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/X_4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/X_4.dir/build: X_4

.PHONY : CMakeFiles/X_4.dir/build

CMakeFiles/X_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/X_4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/X_4.dir/clean

CMakeFiles/X_4.dir/depend:
	cd /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jhilario/Documents/portfolio/tcpp_pl/X_4 /Users/jhilario/Documents/portfolio/tcpp_pl/X_4 /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/cmake-build-debug /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/cmake-build-debug /Users/jhilario/Documents/portfolio/tcpp_pl/X_4/cmake-build-debug/CMakeFiles/X_4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/X_4.dir/depend

