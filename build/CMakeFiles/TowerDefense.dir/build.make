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
CMAKE_SOURCE_DIR = "/home/tty1/Bureau/Tower Defense"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/tty1/Bureau/Tower Defense/build"

# Include any dependencies generated for this target.
include CMakeFiles/TowerDefense.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TowerDefense.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TowerDefense.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TowerDefense.dir/flags.make

CMakeFiles/TowerDefense.dir/apps/main.cpp.o: CMakeFiles/TowerDefense.dir/flags.make
CMakeFiles/TowerDefense.dir/apps/main.cpp.o: ../apps/main.cpp
CMakeFiles/TowerDefense.dir/apps/main.cpp.o: CMakeFiles/TowerDefense.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tty1/Bureau/Tower Defense/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TowerDefense.dir/apps/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TowerDefense.dir/apps/main.cpp.o -MF CMakeFiles/TowerDefense.dir/apps/main.cpp.o.d -o CMakeFiles/TowerDefense.dir/apps/main.cpp.o -c "/home/tty1/Bureau/Tower Defense/apps/main.cpp"

CMakeFiles/TowerDefense.dir/apps/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TowerDefense.dir/apps/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tty1/Bureau/Tower Defense/apps/main.cpp" > CMakeFiles/TowerDefense.dir/apps/main.cpp.i

CMakeFiles/TowerDefense.dir/apps/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TowerDefense.dir/apps/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tty1/Bureau/Tower Defense/apps/main.cpp" -o CMakeFiles/TowerDefense.dir/apps/main.cpp.s

CMakeFiles/TowerDefense.dir/src/game.cpp.o: CMakeFiles/TowerDefense.dir/flags.make
CMakeFiles/TowerDefense.dir/src/game.cpp.o: ../src/game.cpp
CMakeFiles/TowerDefense.dir/src/game.cpp.o: CMakeFiles/TowerDefense.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tty1/Bureau/Tower Defense/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TowerDefense.dir/src/game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TowerDefense.dir/src/game.cpp.o -MF CMakeFiles/TowerDefense.dir/src/game.cpp.o.d -o CMakeFiles/TowerDefense.dir/src/game.cpp.o -c "/home/tty1/Bureau/Tower Defense/src/game.cpp"

CMakeFiles/TowerDefense.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TowerDefense.dir/src/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tty1/Bureau/Tower Defense/src/game.cpp" > CMakeFiles/TowerDefense.dir/src/game.cpp.i

CMakeFiles/TowerDefense.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TowerDefense.dir/src/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tty1/Bureau/Tower Defense/src/game.cpp" -o CMakeFiles/TowerDefense.dir/src/game.cpp.s

CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o: CMakeFiles/TowerDefense.dir/flags.make
CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o: ../src/assetsmanager.cpp
CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o: CMakeFiles/TowerDefense.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tty1/Bureau/Tower Defense/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o -MF CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o.d -o CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o -c "/home/tty1/Bureau/Tower Defense/src/assetsmanager.cpp"

CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tty1/Bureau/Tower Defense/src/assetsmanager.cpp" > CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.i

CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tty1/Bureau/Tower Defense/src/assetsmanager.cpp" -o CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.s

CMakeFiles/TowerDefense.dir/src/vector2.cpp.o: CMakeFiles/TowerDefense.dir/flags.make
CMakeFiles/TowerDefense.dir/src/vector2.cpp.o: ../src/vector2.cpp
CMakeFiles/TowerDefense.dir/src/vector2.cpp.o: CMakeFiles/TowerDefense.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tty1/Bureau/Tower Defense/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TowerDefense.dir/src/vector2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TowerDefense.dir/src/vector2.cpp.o -MF CMakeFiles/TowerDefense.dir/src/vector2.cpp.o.d -o CMakeFiles/TowerDefense.dir/src/vector2.cpp.o -c "/home/tty1/Bureau/Tower Defense/src/vector2.cpp"

CMakeFiles/TowerDefense.dir/src/vector2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TowerDefense.dir/src/vector2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tty1/Bureau/Tower Defense/src/vector2.cpp" > CMakeFiles/TowerDefense.dir/src/vector2.cpp.i

CMakeFiles/TowerDefense.dir/src/vector2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TowerDefense.dir/src/vector2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tty1/Bureau/Tower Defense/src/vector2.cpp" -o CMakeFiles/TowerDefense.dir/src/vector2.cpp.s

CMakeFiles/TowerDefense.dir/src/instances.cpp.o: CMakeFiles/TowerDefense.dir/flags.make
CMakeFiles/TowerDefense.dir/src/instances.cpp.o: ../src/instances.cpp
CMakeFiles/TowerDefense.dir/src/instances.cpp.o: CMakeFiles/TowerDefense.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/tty1/Bureau/Tower Defense/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TowerDefense.dir/src/instances.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TowerDefense.dir/src/instances.cpp.o -MF CMakeFiles/TowerDefense.dir/src/instances.cpp.o.d -o CMakeFiles/TowerDefense.dir/src/instances.cpp.o -c "/home/tty1/Bureau/Tower Defense/src/instances.cpp"

CMakeFiles/TowerDefense.dir/src/instances.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TowerDefense.dir/src/instances.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/tty1/Bureau/Tower Defense/src/instances.cpp" > CMakeFiles/TowerDefense.dir/src/instances.cpp.i

CMakeFiles/TowerDefense.dir/src/instances.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TowerDefense.dir/src/instances.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/tty1/Bureau/Tower Defense/src/instances.cpp" -o CMakeFiles/TowerDefense.dir/src/instances.cpp.s

# Object files for target TowerDefense
TowerDefense_OBJECTS = \
"CMakeFiles/TowerDefense.dir/apps/main.cpp.o" \
"CMakeFiles/TowerDefense.dir/src/game.cpp.o" \
"CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o" \
"CMakeFiles/TowerDefense.dir/src/vector2.cpp.o" \
"CMakeFiles/TowerDefense.dir/src/instances.cpp.o"

# External object files for target TowerDefense
TowerDefense_EXTERNAL_OBJECTS =

TowerDefense: CMakeFiles/TowerDefense.dir/apps/main.cpp.o
TowerDefense: CMakeFiles/TowerDefense.dir/src/game.cpp.o
TowerDefense: CMakeFiles/TowerDefense.dir/src/assetsmanager.cpp.o
TowerDefense: CMakeFiles/TowerDefense.dir/src/vector2.cpp.o
TowerDefense: CMakeFiles/TowerDefense.dir/src/instances.cpp.o
TowerDefense: CMakeFiles/TowerDefense.dir/build.make
TowerDefense: CMakeFiles/TowerDefense.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/tty1/Bureau/Tower Defense/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable TowerDefense"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TowerDefense.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TowerDefense.dir/build: TowerDefense
.PHONY : CMakeFiles/TowerDefense.dir/build

CMakeFiles/TowerDefense.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TowerDefense.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TowerDefense.dir/clean

CMakeFiles/TowerDefense.dir/depend:
	cd "/home/tty1/Bureau/Tower Defense/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/tty1/Bureau/Tower Defense" "/home/tty1/Bureau/Tower Defense" "/home/tty1/Bureau/Tower Defense/build" "/home/tty1/Bureau/Tower Defense/build" "/home/tty1/Bureau/Tower Defense/build/CMakeFiles/TowerDefense.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TowerDefense.dir/depend

