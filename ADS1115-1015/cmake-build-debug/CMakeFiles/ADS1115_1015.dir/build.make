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
CMAKE_COMMAND = /home/so/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/so/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/so/gitHub/Embedded-Linux-API/ADS1115-1015

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ADS1115_1015.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ADS1115_1015.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ADS1115_1015.dir/flags.make

CMakeFiles/ADS1115_1015.dir/main.c.o: CMakeFiles/ADS1115_1015.dir/flags.make
CMakeFiles/ADS1115_1015.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/so/gitHub/Embedded-Linux-API/ADS1115-1015/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ADS1115_1015.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ADS1115_1015.dir/main.c.o   -c /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/main.c

CMakeFiles/ADS1115_1015.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ADS1115_1015.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/main.c > CMakeFiles/ADS1115_1015.dir/main.c.i

CMakeFiles/ADS1115_1015.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ADS1115_1015.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/main.c -o CMakeFiles/ADS1115_1015.dir/main.c.s

CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.o: CMakeFiles/ADS1115_1015.dir/flags.make
CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.o: ../libs/ADS1115-1015.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/so/gitHub/Embedded-Linux-API/ADS1115-1015/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.o   -c /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/libs/ADS1115-1015.c

CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/libs/ADS1115-1015.c > CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.i

CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/libs/ADS1115-1015.c -o CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.s

# Object files for target ADS1115_1015
ADS1115_1015_OBJECTS = \
"CMakeFiles/ADS1115_1015.dir/main.c.o" \
"CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.o"

# External object files for target ADS1115_1015
ADS1115_1015_EXTERNAL_OBJECTS =

ADS1115_1015: CMakeFiles/ADS1115_1015.dir/main.c.o
ADS1115_1015: CMakeFiles/ADS1115_1015.dir/libs/ADS1115-1015.c.o
ADS1115_1015: CMakeFiles/ADS1115_1015.dir/build.make
ADS1115_1015: CMakeFiles/ADS1115_1015.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/so/gitHub/Embedded-Linux-API/ADS1115-1015/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ADS1115_1015"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ADS1115_1015.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ADS1115_1015.dir/build: ADS1115_1015

.PHONY : CMakeFiles/ADS1115_1015.dir/build

CMakeFiles/ADS1115_1015.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ADS1115_1015.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ADS1115_1015.dir/clean

CMakeFiles/ADS1115_1015.dir/depend:
	cd /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/so/gitHub/Embedded-Linux-API/ADS1115-1015 /home/so/gitHub/Embedded-Linux-API/ADS1115-1015 /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/cmake-build-debug /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/cmake-build-debug /home/so/gitHub/Embedded-Linux-API/ADS1115-1015/cmake-build-debug/CMakeFiles/ADS1115_1015.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ADS1115_1015.dir/depend
