cmake_minimum_required(VERSION 3.16)

# Automatically set project name based on current directory
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES C CXX)

# C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to build as library
option(BUILD_AS_LIBRARY "Build as static library instead of executable" OFF)

# Include the 'include' directory
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# Glob all source files (.c and .cpp) recursively
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Create target based on BUILD_AS_LIBRARY option
if(BUILD_AS_LIBRARY)
    add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
else()
    add_executable(${PROJECT_NAME} ${SRC_FILES})
endif()

# Link include directory to the target
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

# Enable Wall and Werror
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)
elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
endif()
