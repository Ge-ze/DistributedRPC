# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chengyongtao/VScode/DistributedRPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chengyongtao/VScode/DistributedRPC/build

# Include any dependencies generated for this target.
include example/caller/CMakeFiles/caller.dir/depend.make

# Include the progress variables for this target.
include example/caller/CMakeFiles/caller.dir/progress.make

# Include the compile flags for this target's objects.
include example/caller/CMakeFiles/caller.dir/flags.make

example/caller/CMakeFiles/caller.dir/calluservice.cc.o: example/caller/CMakeFiles/caller.dir/flags.make
example/caller/CMakeFiles/caller.dir/calluservice.cc.o: ../example/caller/calluservice.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengyongtao/VScode/DistributedRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/caller/CMakeFiles/caller.dir/calluservice.cc.o"
	cd /home/chengyongtao/VScode/DistributedRPC/build/example/caller && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/caller.dir/calluservice.cc.o -c /home/chengyongtao/VScode/DistributedRPC/example/caller/calluservice.cc

example/caller/CMakeFiles/caller.dir/calluservice.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/caller.dir/calluservice.cc.i"
	cd /home/chengyongtao/VScode/DistributedRPC/build/example/caller && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengyongtao/VScode/DistributedRPC/example/caller/calluservice.cc > CMakeFiles/caller.dir/calluservice.cc.i

example/caller/CMakeFiles/caller.dir/calluservice.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/caller.dir/calluservice.cc.s"
	cd /home/chengyongtao/VScode/DistributedRPC/build/example/caller && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengyongtao/VScode/DistributedRPC/example/caller/calluservice.cc -o CMakeFiles/caller.dir/calluservice.cc.s

example/caller/CMakeFiles/caller.dir/__/user.pb.cc.o: example/caller/CMakeFiles/caller.dir/flags.make
example/caller/CMakeFiles/caller.dir/__/user.pb.cc.o: ../example/user.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chengyongtao/VScode/DistributedRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object example/caller/CMakeFiles/caller.dir/__/user.pb.cc.o"
	cd /home/chengyongtao/VScode/DistributedRPC/build/example/caller && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/caller.dir/__/user.pb.cc.o -c /home/chengyongtao/VScode/DistributedRPC/example/user.pb.cc

example/caller/CMakeFiles/caller.dir/__/user.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/caller.dir/__/user.pb.cc.i"
	cd /home/chengyongtao/VScode/DistributedRPC/build/example/caller && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chengyongtao/VScode/DistributedRPC/example/user.pb.cc > CMakeFiles/caller.dir/__/user.pb.cc.i

example/caller/CMakeFiles/caller.dir/__/user.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/caller.dir/__/user.pb.cc.s"
	cd /home/chengyongtao/VScode/DistributedRPC/build/example/caller && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chengyongtao/VScode/DistributedRPC/example/user.pb.cc -o CMakeFiles/caller.dir/__/user.pb.cc.s

# Object files for target caller
caller_OBJECTS = \
"CMakeFiles/caller.dir/calluservice.cc.o" \
"CMakeFiles/caller.dir/__/user.pb.cc.o"

# External object files for target caller
caller_EXTERNAL_OBJECTS =

../bin/caller: example/caller/CMakeFiles/caller.dir/calluservice.cc.o
../bin/caller: example/caller/CMakeFiles/caller.dir/__/user.pb.cc.o
../bin/caller: example/caller/CMakeFiles/caller.dir/build.make
../bin/caller: ../lib/librpc.a
../bin/caller: example/caller/CMakeFiles/caller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chengyongtao/VScode/DistributedRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../../bin/caller"
	cd /home/chengyongtao/VScode/DistributedRPC/build/example/caller && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/caller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/caller/CMakeFiles/caller.dir/build: ../bin/caller

.PHONY : example/caller/CMakeFiles/caller.dir/build

example/caller/CMakeFiles/caller.dir/clean:
	cd /home/chengyongtao/VScode/DistributedRPC/build/example/caller && $(CMAKE_COMMAND) -P CMakeFiles/caller.dir/cmake_clean.cmake
.PHONY : example/caller/CMakeFiles/caller.dir/clean

example/caller/CMakeFiles/caller.dir/depend:
	cd /home/chengyongtao/VScode/DistributedRPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chengyongtao/VScode/DistributedRPC /home/chengyongtao/VScode/DistributedRPC/example/caller /home/chengyongtao/VScode/DistributedRPC/build /home/chengyongtao/VScode/DistributedRPC/build/example/caller /home/chengyongtao/VScode/DistributedRPC/build/example/caller/CMakeFiles/caller.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/caller/CMakeFiles/caller.dir/depend

