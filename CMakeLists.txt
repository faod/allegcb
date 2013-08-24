cmake_minimum_required(VERSION 2.8)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
	message(FATAL_ERROR, "Building on OSX is not currently supported !")
endif()

#-----------#
# Configure
#-----------#

project(alleg-codebase C)

# The user must fill these variables if the files arnt in the paths envvar
set(ALLEGRO_HOME "" CACHE PATH "Allegro Home path on windows, must contains include, lib and bin directories.")
set(ALLEG_VERSION "5.0.7" CACHE STRING "Your installed allegro version e.g. '5.0.7'.")

option(ALLEGRO_STATICLINK "static link to allegro ?" off)
option(ALLEGRO_LINK_DBG "link with DEBUG libs ?" off)
option(ALLEGRO_LINK_MONOLITH "link with Monolith builds ? (Windows only)" off)
option(ALLEGRO_LINK_MT "link with MT libs (Windows only) ?" off)

include_directories("${ALLEGRO_HOME}/include")
link_directories("${ALLEGRO_HOME}/lib")

#-----------#
#    Env
#-----------#

include("${PROJECT_SOURCE_DIR}/cmake/alleg.cmake")
make_libs_filenames(deps ${ALLEG_VERSION})
append_deps(deps "${deps}")

#-----------#
#   Build
#-----------#

file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
add_executable(map_viewer ${sources})
set_target_properties(map_viewer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "build")
if(ALLEGRO_STATICLINK)
	set_target_properties(map_viewer PROPERTIES COMPILE_DEFINITIONS "ALLEGRO_STATICLINK")
endif(ALLEGRO_STATICLINK)
target_link_libraries(map_viewer ${deps})
