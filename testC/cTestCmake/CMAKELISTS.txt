cmake_minimum_required(VERSION 3.5.0)

## Set parameter of project
# set the project name 
project(cppTest VERSION 1.0)

set(AUTHOR "WASHINGOTN RUAN") 
set(SOURCECODE_DIR "${PROJECT_BINARY_DIR}/../src/")
set(HEADER_DIR "${PROJECT_BINARY_DIR}/../include/")
set(PROJECT "cTest")
#set(PROJECT_SOURCE_DIR "${SOURCECODE_DIR}")

# set debug flags
add_definitions(
    -DTWDP_MEMPOOL_DEBUG        #enable mempool debug
    -DTWDP_MALLOC_DEBUG         #enable malloc/free debug
)

## Set compile information.
# enable debug mode
set(ModeOption -O0)
# set error flags
set(WERROR_FLAGS -W -Wall -g)
# set compiler flags
set(CFLAGS -pthread ${CFLAGS} ${ModeOption} ${WERROR_FLAGS})
add_compile_options(${CFLAGS})

#add_subdirectory()
#add_library(L2ScheDl ${DIR_LIB_SRCS})
if (CMAKE_BUILD_TYPE STREQUAL DEBUG)
    add_definitions(-DDEBUG)
endif()

# print some information.
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message(STATUS "AUTHOR = ${AUTHOR}")
message(STATUS "SOURCECODE_DIR = ${SOURCECODE_DIR}")
message(STATUS "HEADER_DIR = ${HEADER_DIR}")
message(STATUS "DIR_LIB_SRCS = ${DIR_LIB_SRCS}")
message(STATUS "SOURCECODE_DIR = ${SOURCECODE_DIR}")

# add source file directory.
include_directories(${HEADER_DIR})
aux_source_directory(./src DIR_LIB_SRCS)

# add the executable.
add_executable(${PROJECT} ${DIR_LIB_SRCS})

# End of this file.
