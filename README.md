# CMake_GoogleTest

How to build this project, follow these steps:
```console
# Navigate to the root of your project directory
cd /path/to/my_project

# Create a build directory and navigate into it
mkdir build
cd build

# Run CMake to configure the project
cmake ..
# New in cmake version 3.24
cmake .. --fresh

# Build the project
make

# Install the project to bin
sudo make install

# Run the tests
ctest

# Run the app
my_app

# Check dependency
ldd my_test
```

Why need sudo make install ? \
Because gtest have to be installed in /usr/..., we have to "sudo make install" to let get sufficient permission
```console
-- Installing: /usr/local/include/gtest/internal/custom/gtest.h
-- Installing: /usr/local/include/gtest/internal/custom/gtest-printers.h
-- Installing: /usr/local/include/gtest/gtest-test-part.h
-- Installing: /usr/local/include/gtest/gtest.h
-- Installing: /usr/local/include/gtest/gtest_prod.h
-- Installing: /usr/local/include/gtest/gtest-printers.h
-- Installing: /usr/local/lib/libgtest.a        or   .so
-- Installing: /usr/local/lib/libgtest_main.a   or   .so
-- Installing: /usr/local/lib/pkgconfig/gtest.pc
-- Installing: /usr/local/lib/pkgconfig/gtest_main.pc
-- Installing: /usr/local/lib/cmake/GTest/GTestConfig.cmake
```

## How to install Google Test library

### Method 1: Using Package Manager
```console
# Install Google Test: Install the libgtest-dev package:
sudo apt install libgtest-dev

# Build Google Test Libraries: The libgtest-dev package provides the source code for Google Test, but not the compiled libraries. You'll need to build them manually:
sudo apt install cmake
cd /usr/src/googletest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
# -DBUILD_SHARED_LIBS=ON parameter builds GoogleTest libraries as shared libraries. Otherwise, the libraries are built as static libraries.

# Verify Installation: The libraries should now be installed in /usr/lib. You can verify that they are there:
ls /usr/lib | grep gtest
```

### Method 2: Building from Source
```console
# Install Dependencies: Ensure you have the necessary tools for building from source:
sudo apt update
sudo apt install cmake g++ git

# Clone Google Test Repository: Clone the Google Test repository from GitHub
git clone https://github.com/google/googletest.git
cd googletest

# Build and Install Google Test: Create a build directory, compile, and install Google Test:
mkdir build
cd build
cmake ..
make
sudo make install
# -DBUILD_SHARED_LIBS=ON parameter builds GoogleTest libraries as shared libraries. Otherwise, the libraries are built as static libraries.

# Verify Installation: Check if Google Test libraries are in the system:
ls /usr/local/lib | grep gtest
```

### Method 3: Fetch via CMakkeLists.txt
```console
# Find google test
find_package(GTest REQUIRED)

# Fetch and Build
if (NOT GTest_FOUND)
    # Download and install GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
    )

    # CMake does not define BUILD_SHARED_LIBS by default, but projects often create a cache entry for it using the option()
    # Set BUILD_SHARED_LIBS on top level to bring it to the subdirectory
    option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
    # Re-set BUILD_SHARED_LIBS if neccessary
    #set(BUILD_SHARED_LIBS OFF)
    #message(STATUS "shared ${BUILD_SHARED_LIBS}")

    # Method 1: Make available
    FetchContent_MakeAvailable(googletest)

    # Method 2: Subdirectory
    # Populate the content
    #FetchContent_Populate(googletest)
    # Add GoogleTest as a subdirectory
    #add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
```

## About find_package() in CMake

### In CMake, there are two mode to include library variables:
- Module mode： \
  It is the default mode. CMake official will install and defind a list of Find<LibaryName>.cmake in /usr/share/cmake-<version>/Modules (when install CMake onto the Linux), and those configuration can help us to include the libraries with ease.
- Config mode： \
  For non-official predfined libraries, we have to include the library using config mode. CMake will enter config mode when module mode fail or under setting to config mode in find_package().

### What does .cmake include ?
- Neccessary variable:
* <LibaryName>_FOUND
* <LibaryName>_INCLUDE_DIR
* <LibaryName>_INCLUDES or <LibaryName>_LIBRARY or <LibaryName>_LIBRARIES
- Addiitonal variable:
* version
* debug or release
* namespace
* ...
```console
# Example of .cmake files
# glog (non-official)
# /usr/local/include/glog/
#
# glog/glog-modules.cmake
# glog-config.cmake
# glog-config-version.cmake
# glog-targets.cmake
# glog-targets-noconfig.cmake or targets-release.cmake


# Basic usage
find_package(<library>)
# If library is a must
find_package(<library> REQUIRED)
# Config mode
find_package(<library> CONFIG REQUIRED)
# Restrict version and components
# 1.79 specific the version 
# COMPONENTS date_time specifies that you are interested in. Boost is a collection of libraries, and each library is organized into components.
find_package(Boost 1.79 COMPONENTS date_time)


# Example of usage
find_package(<library>)

add_executable(app app.c)

if(CURL_FOUND)
    target_include_directories(app PRIVATE ${<library>_INCLUDE_DIR})
    target_link_libraries(app ${<library>_LIBRARY})
else(CURL_FOUND)
    message(FATAL_ERROR ”<library> library not found”)
endif(CURL_FOUND)
```

### Exampele of self-defined .cmake files
directory tree
```console
├── lib<...>.c
├── lib<...>.h
├── Makefile
└── test
    ├── addtest.c
    ├── cmake
    │   └── FindADD.cmake
    └── CMakeLists.txt
```
CMakeLists.txt
```console
cmake_minimum_required(VERSION 3.16)
project(test)

# for find_pakcage() to find our self-defined library
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

add_executable(addtest addtest.cc)

find_package(<...>)
if (<...>_FOUND)
    target_include_directories(addtest PRIVATE ${<...>_INCLUDE_DIR})
    target_link_libraries(addtest ${<...>_LIBRARY})
else ()
    message(FATAL_ERROR "<...> library not found")
endif ()
```
Find<...>.cmake
```console
find_path(<...>_INCLUDE_DIR lib<...>.h /usr/include/ /usr/local/include ${CMAKE_SOURCE_DIR}/ModuleMode)

find_library(<...>_LIBRARY lib<...>.a lib<...>.so /usr/lib/ /usr/local/lib/ ${CMAKE_SOURCE_DIR}/ModuleMode)

if (<...>_INCLUDE_DIR AND <...>_LIBRARY)
	set(<...>_FOUND TRUE)
endif (<...>_INCLUDE_DIR AND <...>_LIBRARY)
```

## Common feature / syntax of CMake

### Add sub directory (sub-project)
```console
add_subdirectory(sub_directory)
```

### Include header
```console
# for all
include_directories()

# only target
target_include_directories()
```

### Add app or lib
```console
# app
add_executable(app app.cpp)

# lib
add_library(lib STATIC lib.cpp)
```

### link or load
C code will often link multiple libraryies to build application.
Static linkage is the basic level to link among libraries (.a file).
Dynamic linkage is a way link shared library (.so file). (app can share library to save memory usage)
Dynamic loaded is another way to only load the library if it's necessary (via using ldopen) \
Ref: https://makori-mildred.medium.com/how-to-create-a-dynamic-library-in-c-and-how-to-use-it-30c304f399a4
```console
# for all
link_library(...)

# only target
target_link_library(<target> ...)
```
We don't need to defined whether it is static link or shared link.
Other feature:
- PUBLIC - This property is for me and everyone who depends on me is going to get this property.
- PRIVATE - This property is just for me. Whoever depends on me is not going to get this.
- INTERFACE - I do not need this for myself. But anyone who depends on me will get this property. \
Ref: https://www.youtube.com/watch?v=ARZd-fSUJXY

### Add Dependencies
```console
# lib
add_library(lib1 STATIC lib1.cpp)
add_library(lib2 STATIC lib2.cpp)

# lib2 depend on lib1
add_dependencies(lib2 lib1)
```
