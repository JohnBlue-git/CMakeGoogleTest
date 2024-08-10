# CMake_GoogleTest_Note

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
Run the tests:

bash
複製程式碼
ctest
This setup assumes you're using CMake version 3.14 or higher and that you have Google Test available online. Adjust the paths and versions according to your needs.