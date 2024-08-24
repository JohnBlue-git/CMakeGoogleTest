# CMake_GoogleTest

Building the Project
To build the project, follow these steps:

Navigate to the root of your project directory:

bash
複製程式碼
cd /path/to/my_project
Create a build directory and navigate into it:

bash
複製程式碼
mkdir build
cd build
Run CMake to configure the project:

bash
複製程式碼
cmake ..
Build the project:

bash
複製程式碼
make

make install

Run the tests:

bash
複製程式碼
ctest
This setup assumes you're using CMake version 3.14 or higher and that you have Google Test available online. Adjust the paths and versions according to your needs.


若 found gtest
Found GTest: /opt/conda/lib/cmake/GTest/GTestConfig.cmake (found version "1.11.0") 

若fetch

??? 需要 sudo make install

but because gtest have to be installed in /usr/..., we have to "sudo make install" to let get sufficient permission

-- Installing: /usr/local/include/gtest/internal/custom/gtest.h
-- Installing: /usr/local/include/gtest/internal/custom/gtest-printers.h
-- Installing: /usr/local/include/gtest/gtest-test-part.h
-- Installing: /usr/local/include/gtest/gtest.h
-- Installing: /usr/local/include/gtest/gtest_prod.h
-- Installing: /usr/local/include/gtest/gtest-printers.h
-- Installing: /usr/local/lib/libgtest.a
-- Installing: /usr/local/lib/libgtest_main.a
-- Installing: /usr/local/lib/pkgconfig/gtest.pc
-- Installing: /usr/local/lib/pkgconfig/gtest_main.pc
-- Installing: /workspaces/CMake_GoogleTest_Note/bin/my_app
-- Installing: /workspaces/CMake_GoogleTest_Note/bin/my_test





... find_package
https://www.cnblogs.com/codingbigdog/p/16831635.html
需要header files跟library
'''

'''
後來就整合在一起


https://stackoverflow.com/questions/20746936/what-use-is-find-package-when-you-need-to-specify-cmake-module-path
然後有分成 config / module

Module模式和Config模式的区别：
Module模式：find_package命令基础工作模式(Basic Signature)，也是默认工作模式。
Config模式：find_package命令高级工作模式(Full Signature)。 只有在find_package()中指定CONFIG、NO_MODULE等关键字，或者Module模式查找失败后才会进入到Config模式。


对于原生支持Cmake编译和安装的库通常会安装Config模式的配置文件到对应目录，这个配置文件直接配置了头文件库文件的路径以及各种cmake变量供find_package使用。而对于非由cmake编译的项目，我们通常会编写一个Find.cmake，通过脚本来获取头文件、库文件等信息。通常，原生支持cmake的项目库安装时会拷贝一份XXXConfig.cmake到系统目录中，因此在没有显式指定搜索路径时也可以顺利找到。


为了方便我们在项目中引入外部依赖包，cmake官方为我们预定义了许多寻找依赖包的Module，他们存储在path_to_your_cmake/share/cmake-<version>/Modules目录下。每个以Find<LibaryName>.cmake命名的文件都可以帮我们找到一个包。
官方定义的.cmake文件在/usr/share/cmake-3.24/Modules




if (NOT XXX_FOUND)
    # message can stop and return from cmake process
    message(FATAL_ERROR "Google Test not found. Please install it.")
endif()










以下解釋就好 不用再創一個


2.编写自己的Find.cmake模块
项目的目录结构：

├── libadd.cc
├── libadd.h
├── Makefile
└── test
    ├── addtest.cc
    ├── cmake
    │   └── FindADD.cmake
    └── CMakeLists.txt
具体内容如下：
libadd.h

int add(int i, int j);
libadd.cc

#include "libadd.h"
 
int add(int i, int j)
{
	return i + j;
}
Makefile

# 1、准备工作，编译方式、目标文件名、依赖库路径的定义。
CC = g++
CFLAGS  := -Wall -O3 -std=c++11 

OBJS = libadd.o #.o文件与.cpp文件同名
LIB = libadd.so # 目标文件名
INCLUDE = ./ # 头文件目录
HEADER = libadd.h # 头文件

all : $(LIB)

# 2. 生成.o文件 
$(OBJS) : libadd.cc
	$(CC) $(CFLAGS) -I ./ -fpic -c $< -o $@

# 3. 生成动态库文件
$(LIB) : $(OBJS)
	rm -f $@
	g++ $(OBJS) -shared -o $@ 
	rm -f $(OBJS)


# 4. 删除中间过程生成的文件 
clean:
	rm -f $(OBJS) $(TARGET) $(LIB)

# 5.安装文件
install:
	cp $(LIB) /usr/lib
	cp $(HEADER) /usr/include
编译和安装动态库：

make
sudo make install
addtest.cc

#include <stdio.h>
#include <stdlib.h>
#include "libadd.h"
 
int main(int argc, char *argv[]) 
{
	printf("1 + 2 = %d\n", add(1, 2));
	return 0;
}
CMakeLists.txt

cmake_minimum_required(VERSION 3.16)
project(test) 
# 将项目目录下的cmake文件夹加入到CMAKE_MODULE_PATH中，让find_pakcage能够找到我们自定义的函数库
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
add_executable(addtest addtest.cc)
find_package(ADD)
if(ADD_FOUND)
    target_include_directories(addtest PRIVATE ${ADD_INCLUDE_DIR})
    target_link_libraries(addtest ${ADD_LIBRARY})
else(ADD_FOUND)
    message(FATAL_ERROR "ADD library not found")
endif(ADD_FOUND)
FindADD.cmake

# 在指定目录下寻找头文件和动态库文件的位置，可以指定多个目标路径
find_path(ADD_INCLUDE_DIR libadd.h /usr/include/ /usr/local/include ${CMAKE_SOURCE_DIR}/ModuleMode)
find_library(ADD_LIBRARY libadd.so  /usr/lib/ /usr/local/lib/ ${CMAKE_SOURCE_DIR}/ModuleMode)

if (ADD_INCLUDE_DIR AND ADD_LIBRARY)
	set(ADD_FOUND TRUE)
endif (ADD_INCLUDE_DIR AND ADD_LIBRARY)
编译和执行：

cd test
mkdir build
cd build
cmake ..
make
./addtest
输出：
1 + 2 = 3







Explicit Dependencies: Using add_dependencies, you can explicitly specify that one target should be built before another, regardless of linking:

cmake
複製程式碼
add_library(lib1 STATIC lib1.cpp)
add_library(lib2 STATIC lib2.cpp)
add_dependencies(lib2 lib1)




target_link_library ...

PUBLIC - This property is for me and everyone who depends on me is going to get this property.
PRIVATE - This property is just for me. Whoever depends on me is not going to get this.
INTERFACE - I do not need this for myself. But anyone who depends on me will get this property.
Watch this video for better understanding - https://www.youtube.com/watch?v=ARZd-fSUJXY

but don't need to defined whether it is static link or shared link




也解釋一下
<target>_include ...
include ...
...


也解釋一下
sub directory



!!!

dynamic link

dynamic load
才會用到ldopen

都要用到.so

https://makori-mildred.medium.com/how-to-create-a-dynamic-library-in-c-and-how-to-use-it-30c304f399a4
