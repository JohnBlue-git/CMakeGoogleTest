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

make install

Run the tests:

bash
複製程式碼
ctest
This setup assumes you're using CMake version 3.14 or higher and that you have Google Test available online. Adjust the paths and versions according to your needs.



??? 需要 sudo make install

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