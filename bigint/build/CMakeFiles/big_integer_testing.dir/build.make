# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build

# Include any dependencies generated for this target.
include CMakeFiles/big_integer_testing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/big_integer_testing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/big_integer_testing.dir/flags.make

CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o: CMakeFiles/big_integer_testing.dir/flags.make
CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o: ../big_integer_testing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o -c /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/big_integer_testing.cpp

CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/big_integer_testing.cpp > CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.i

CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/big_integer_testing.cpp -o CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.s

CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o.requires:

.PHONY : CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o.requires

CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o.provides: CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o.requires
	$(MAKE) -f CMakeFiles/big_integer_testing.dir/build.make CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o.provides.build
.PHONY : CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o.provides

CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o.provides.build: CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o


CMakeFiles/big_integer_testing.dir/big_integer.cpp.o: CMakeFiles/big_integer_testing.dir/flags.make
CMakeFiles/big_integer_testing.dir/big_integer.cpp.o: ../big_integer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/big_integer_testing.dir/big_integer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer_testing.dir/big_integer.cpp.o -c /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/big_integer.cpp

CMakeFiles/big_integer_testing.dir/big_integer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer_testing.dir/big_integer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/big_integer.cpp > CMakeFiles/big_integer_testing.dir/big_integer.cpp.i

CMakeFiles/big_integer_testing.dir/big_integer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer_testing.dir/big_integer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/big_integer.cpp -o CMakeFiles/big_integer_testing.dir/big_integer.cpp.s

CMakeFiles/big_integer_testing.dir/big_integer.cpp.o.requires:

.PHONY : CMakeFiles/big_integer_testing.dir/big_integer.cpp.o.requires

CMakeFiles/big_integer_testing.dir/big_integer.cpp.o.provides: CMakeFiles/big_integer_testing.dir/big_integer.cpp.o.requires
	$(MAKE) -f CMakeFiles/big_integer_testing.dir/build.make CMakeFiles/big_integer_testing.dir/big_integer.cpp.o.provides.build
.PHONY : CMakeFiles/big_integer_testing.dir/big_integer.cpp.o.provides

CMakeFiles/big_integer_testing.dir/big_integer.cpp.o.provides.build: CMakeFiles/big_integer_testing.dir/big_integer.cpp.o


CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o: CMakeFiles/big_integer_testing.dir/flags.make
CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o: ../gtest/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o -c /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/gtest/gtest-all.cc

CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/gtest/gtest-all.cc > CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.i

CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/gtest/gtest-all.cc -o CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.s

CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o.requires:

.PHONY : CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o.requires

CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o.provides: CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o.requires
	$(MAKE) -f CMakeFiles/big_integer_testing.dir/build.make CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o.provides.build
.PHONY : CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o.provides

CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o.provides.build: CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o


CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o: CMakeFiles/big_integer_testing.dir/flags.make
CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o: ../gtest/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o -c /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/gtest/gtest_main.cc

CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/gtest/gtest_main.cc > CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.i

CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/gtest/gtest_main.cc -o CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.s

CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o.requires:

.PHONY : CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o.requires

CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o.provides: CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o.requires
	$(MAKE) -f CMakeFiles/big_integer_testing.dir/build.make CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o.provides.build
.PHONY : CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o.provides

CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o.provides.build: CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o


# Object files for target big_integer_testing
big_integer_testing_OBJECTS = \
"CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o" \
"CMakeFiles/big_integer_testing.dir/big_integer.cpp.o" \
"CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o" \
"CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o"

# External object files for target big_integer_testing
big_integer_testing_EXTERNAL_OBJECTS =

big_integer_testing: CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o
big_integer_testing: CMakeFiles/big_integer_testing.dir/big_integer.cpp.o
big_integer_testing: CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o
big_integer_testing: CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o
big_integer_testing: CMakeFiles/big_integer_testing.dir/build.make
big_integer_testing: CMakeFiles/big_integer_testing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable big_integer_testing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/big_integer_testing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/big_integer_testing.dir/build: big_integer_testing

.PHONY : CMakeFiles/big_integer_testing.dir/build

CMakeFiles/big_integer_testing.dir/requires: CMakeFiles/big_integer_testing.dir/big_integer_testing.cpp.o.requires
CMakeFiles/big_integer_testing.dir/requires: CMakeFiles/big_integer_testing.dir/big_integer.cpp.o.requires
CMakeFiles/big_integer_testing.dir/requires: CMakeFiles/big_integer_testing.dir/gtest/gtest-all.cc.o.requires
CMakeFiles/big_integer_testing.dir/requires: CMakeFiles/big_integer_testing.dir/gtest/gtest_main.cc.o.requires

.PHONY : CMakeFiles/big_integer_testing.dir/requires

CMakeFiles/big_integer_testing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/big_integer_testing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/big_integer_testing.dir/clean

CMakeFiles/big_integer_testing.dir/depend:
	cd /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build /mnt/c/Users/Erika/Documents/ITMO/1/c++/bigint/build/CMakeFiles/big_integer_testing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/big_integer_testing.dir/depend

