# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/paco/robocomp/components/rtps-graph/prueba3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paco/robocomp/components/rtps-graph/prueba3

# Include any dependencies generated for this target.
include CMakeFiles/cadena_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cadena_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cadena_lib.dir/flags.make

CMakeFiles/cadena_lib.dir/cadena.cxx.o: CMakeFiles/cadena_lib.dir/flags.make
CMakeFiles/cadena_lib.dir/cadena.cxx.o: cadena.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paco/robocomp/components/rtps-graph/prueba3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cadena_lib.dir/cadena.cxx.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cadena_lib.dir/cadena.cxx.o -c /home/paco/robocomp/components/rtps-graph/prueba3/cadena.cxx

CMakeFiles/cadena_lib.dir/cadena.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cadena_lib.dir/cadena.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paco/robocomp/components/rtps-graph/prueba3/cadena.cxx > CMakeFiles/cadena_lib.dir/cadena.cxx.i

CMakeFiles/cadena_lib.dir/cadena.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cadena_lib.dir/cadena.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paco/robocomp/components/rtps-graph/prueba3/cadena.cxx -o CMakeFiles/cadena_lib.dir/cadena.cxx.s

# Object files for target cadena_lib
cadena_lib_OBJECTS = \
"CMakeFiles/cadena_lib.dir/cadena.cxx.o"

# External object files for target cadena_lib
cadena_lib_EXTERNAL_OBJECTS =

libcadena_lib.a: CMakeFiles/cadena_lib.dir/cadena.cxx.o
libcadena_lib.a: CMakeFiles/cadena_lib.dir/build.make
libcadena_lib.a: CMakeFiles/cadena_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paco/robocomp/components/rtps-graph/prueba3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcadena_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/cadena_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cadena_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cadena_lib.dir/build: libcadena_lib.a

.PHONY : CMakeFiles/cadena_lib.dir/build

CMakeFiles/cadena_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cadena_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cadena_lib.dir/clean

CMakeFiles/cadena_lib.dir/depend:
	cd /home/paco/robocomp/components/rtps-graph/prueba3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paco/robocomp/components/rtps-graph/prueba3 /home/paco/robocomp/components/rtps-graph/prueba3 /home/paco/robocomp/components/rtps-graph/prueba3 /home/paco/robocomp/components/rtps-graph/prueba3 /home/paco/robocomp/components/rtps-graph/prueba3/CMakeFiles/cadena_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cadena_lib.dir/depend
