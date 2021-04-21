# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /mnt/d/Projects/oatpp/docker-api-swagger-oatpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Projects/oatpp/docker-api-swagger-oatpp

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/d/Projects/oatpp/docker-api-swagger-oatpp/CMakeFiles /mnt/d/Projects/oatpp/docker-api-swagger-oatpp/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/d/Projects/oatpp/docker-api-swagger-oatpp/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named docker-api-swagger

# Build rule for target.
docker-api-swagger: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 docker-api-swagger
.PHONY : docker-api-swagger

# fast build rule for target.
docker-api-swagger/fast:
	$(MAKE) -f CMakeFiles/docker-api-swagger.dir/build.make CMakeFiles/docker-api-swagger.dir/build
.PHONY : docker-api-swagger/fast

#=============================================================================
# Target rules for targets named docker-api-swagger-lib

# Build rule for target.
docker-api-swagger-lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 docker-api-swagger-lib
.PHONY : docker-api-swagger-lib

# fast build rule for target.
docker-api-swagger-lib/fast:
	$(MAKE) -f CMakeFiles/docker-api-swagger-lib.dir/build.make CMakeFiles/docker-api-swagger-lib.dir/build
.PHONY : docker-api-swagger-lib/fast

src/App.o: src/App.cpp.o

.PHONY : src/App.o

# target to build an object file
src/App.cpp.o:
	$(MAKE) -f CMakeFiles/docker-api-swagger.dir/build.make CMakeFiles/docker-api-swagger.dir/src/App.cpp.o
.PHONY : src/App.cpp.o

src/App.i: src/App.cpp.i

.PHONY : src/App.i

# target to preprocess a source file
src/App.cpp.i:
	$(MAKE) -f CMakeFiles/docker-api-swagger.dir/build.make CMakeFiles/docker-api-swagger.dir/src/App.cpp.i
.PHONY : src/App.cpp.i

src/App.s: src/App.cpp.s

.PHONY : src/App.s

# target to generate assembly for a file
src/App.cpp.s:
	$(MAKE) -f CMakeFiles/docker-api-swagger.dir/build.make CMakeFiles/docker-api-swagger.dir/src/App.cpp.s
.PHONY : src/App.cpp.s

src/swagger/Resources.o: src/swagger/Resources.cpp.o

.PHONY : src/swagger/Resources.o

# target to build an object file
src/swagger/Resources.cpp.o:
	$(MAKE) -f CMakeFiles/docker-api-swagger-lib.dir/build.make CMakeFiles/docker-api-swagger-lib.dir/src/swagger/Resources.cpp.o
.PHONY : src/swagger/Resources.cpp.o

src/swagger/Resources.i: src/swagger/Resources.cpp.i

.PHONY : src/swagger/Resources.i

# target to preprocess a source file
src/swagger/Resources.cpp.i:
	$(MAKE) -f CMakeFiles/docker-api-swagger-lib.dir/build.make CMakeFiles/docker-api-swagger-lib.dir/src/swagger/Resources.cpp.i
.PHONY : src/swagger/Resources.cpp.i

src/swagger/Resources.s: src/swagger/Resources.cpp.s

.PHONY : src/swagger/Resources.s

# target to generate assembly for a file
src/swagger/Resources.cpp.s:
	$(MAKE) -f CMakeFiles/docker-api-swagger-lib.dir/build.make CMakeFiles/docker-api-swagger-lib.dir/src/swagger/Resources.cpp.s
.PHONY : src/swagger/Resources.cpp.s

src/swagger/Types.o: src/swagger/Types.cpp.o

.PHONY : src/swagger/Types.o

# target to build an object file
src/swagger/Types.cpp.o:
	$(MAKE) -f CMakeFiles/docker-api-swagger-lib.dir/build.make CMakeFiles/docker-api-swagger-lib.dir/src/swagger/Types.cpp.o
.PHONY : src/swagger/Types.cpp.o

src/swagger/Types.i: src/swagger/Types.cpp.i

.PHONY : src/swagger/Types.i

# target to preprocess a source file
src/swagger/Types.cpp.i:
	$(MAKE) -f CMakeFiles/docker-api-swagger-lib.dir/build.make CMakeFiles/docker-api-swagger-lib.dir/src/swagger/Types.cpp.i
.PHONY : src/swagger/Types.cpp.i

src/swagger/Types.s: src/swagger/Types.cpp.s

.PHONY : src/swagger/Types.s

# target to generate assembly for a file
src/swagger/Types.cpp.s:
	$(MAKE) -f CMakeFiles/docker-api-swagger-lib.dir/build.make CMakeFiles/docker-api-swagger-lib.dir/src/swagger/Types.cpp.s
.PHONY : src/swagger/Types.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... docker-api-swagger"
	@echo "... docker-api-swagger-lib"
	@echo "... src/App.o"
	@echo "... src/App.i"
	@echo "... src/App.s"
	@echo "... src/swagger/Resources.o"
	@echo "... src/swagger/Resources.i"
	@echo "... src/swagger/Resources.s"
	@echo "... src/swagger/Types.o"
	@echo "... src/swagger/Types.i"
	@echo "... src/swagger/Types.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

