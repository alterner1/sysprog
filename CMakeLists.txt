cmake_minimum_required(VERSION 3.5)

project (md5_bf)

# The version number.
set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 0)
set (${PROJECT_NAME}_VERSION_PATCH 0)
set (${PROJECT_NAME}_VERSION_TWEAK 0)
set (${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}.${${PROJECT_NAME}_VERSION_TWEAK}")

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

# set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard
# set(CMAKE_CXX_STANDARD 14)  # enable C++14 standard
# set(CMAKE_CXX_STANDARD 17)  # enable C++17 standard
# or
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp -pthread")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c89")
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c90")
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -fopenmp -pthread")


#add_definitions(-Wall -O2)
# or
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Call configure files on ver.h.in to set the version.
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")
configure_file(
               "${PROJECT_SOURCE_DIR}/include/ver.h.in"
               "${PROJECT_SOURCE_DIR}/include/version.h"
              )
#------------------- Create an executable --------------------------------------
add_subdirectory(src)
file(GLOB 
          CPP_SOURCES "*.c")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE md5) 
install(TARGETS ${PROJECT_NAME}
       EXPORT ${PROJECT_NAME}TARGETS
       LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
       ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
       RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
       INCLUDES DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

# link the new library target with the binary target


#set(SOURCES main.cpp test.c)
#or
#file(GLOB 
#          CPPS "${PROJECT_NAME}/src/*.cpp"
#          C    "${PROJECT_NAME}/src/*.c")

# add_executable(${PROJECT_NAME} main.cpp test.c)
#add_executable(${PROJECT_NAME} ${SOURCES})
# or 
#add_executable(${PROJECT_NAME} ${CPPS} ${C})
# install the target and create export-set
