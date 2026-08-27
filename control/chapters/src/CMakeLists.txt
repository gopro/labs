# CMakeLists.txt
cmake_minimum_required (VERSION 3.5.1)
project (udtacopy)
  
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

file(GLOB SOURCES "*.c")

add_executable(udtacopy ${SOURCES})

if (WIN32)
	SET_TARGET_PROPERTIES(udtacopy PROPERTIES LINK_FLAGS "setargv.obj")
endif (WIN32)