# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /tmp/02-sensor-auslesen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/02-sensor-auslesen/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/02-sensor-auslesen.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/02-sensor-auslesen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/02-sensor-auslesen.dir/flags.make

CMakeFiles/02-sensor-auslesen.dir/main.c.o: CMakeFiles/02-sensor-auslesen.dir/flags.make
CMakeFiles/02-sensor-auslesen.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/02-sensor-auslesen/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/02-sensor-auslesen.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/02-sensor-auslesen.dir/main.c.o   -c /tmp/02-sensor-auslesen/main.c

CMakeFiles/02-sensor-auslesen.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/02-sensor-auslesen.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/02-sensor-auslesen/main.c > CMakeFiles/02-sensor-auslesen.dir/main.c.i

CMakeFiles/02-sensor-auslesen.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/02-sensor-auslesen.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/02-sensor-auslesen/main.c -o CMakeFiles/02-sensor-auslesen.dir/main.c.s

CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.o: CMakeFiles/02-sensor-auslesen.dir/flags.make
CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.o: ../lcd_i2c.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/02-sensor-auslesen/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.o   -c /tmp/02-sensor-auslesen/lcd_i2c.c

CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/02-sensor-auslesen/lcd_i2c.c > CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.i

CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/02-sensor-auslesen/lcd_i2c.c -o CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.s

# Object files for target 02-sensor-auslesen
02__sensor__auslesen_OBJECTS = \
"CMakeFiles/02-sensor-auslesen.dir/main.c.o" \
"CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.o"

# External object files for target 02-sensor-auslesen
02__sensor__auslesen_EXTERNAL_OBJECTS =

02-sensor-auslesen: CMakeFiles/02-sensor-auslesen.dir/main.c.o
02-sensor-auslesen: CMakeFiles/02-sensor-auslesen.dir/lcd_i2c.c.o
02-sensor-auslesen: CMakeFiles/02-sensor-auslesen.dir/build.make
02-sensor-auslesen: CMakeFiles/02-sensor-auslesen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/02-sensor-auslesen/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable 02-sensor-auslesen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/02-sensor-auslesen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/02-sensor-auslesen.dir/build: 02-sensor-auslesen

.PHONY : CMakeFiles/02-sensor-auslesen.dir/build

CMakeFiles/02-sensor-auslesen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/02-sensor-auslesen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/02-sensor-auslesen.dir/clean

CMakeFiles/02-sensor-auslesen.dir/depend:
	cd /tmp/02-sensor-auslesen/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/02-sensor-auslesen /tmp/02-sensor-auslesen /tmp/02-sensor-auslesen/cmake-build-debug /tmp/02-sensor-auslesen/cmake-build-debug /tmp/02-sensor-auslesen/cmake-build-debug/CMakeFiles/02-sensor-auslesen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/02-sensor-auslesen.dir/depend

