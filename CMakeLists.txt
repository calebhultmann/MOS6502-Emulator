cmake_minimum_required(VERSION 3.30)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(chemu6502 VERSION 1.2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) 

# Add dependencies
find_package(GTest CONFIG REQUIRED)

# Main emulator executable
add_executable(Emulator)

# Emulator sources and headers
file(GLOB_RECURSE Emulator_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
)

target_sources(Emulator PRIVATE ${Emulator_SOURCES})

# Emulator include dirs
target_include_directories(Emulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/test
)

# Automatically links to these libs
target_link_libraries(Emulator PRIVATE
    GTest::gtest
)
enable_testing()

# Set configuration properties for Emulator
if(MSVC)
    target_compile_options(Emulator PRIVATE
        /W3
        /MP # multithreaded build
        /WX # warnings as errors
        /ZI # program database for edit and continue
    )
else()
    target_compile_options(Emulator PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Emulator)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(src)
add_subdirectory(test)