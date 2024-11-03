project-root/
├── CMakeLists.txt
├── include/
│   └── your_header_files.h
├── src/
│   └── your_source_files.cpp
└── build/

# Explanation:

cmake_minimum_required(VERSION 3.10): Sets the minimum version of CMake required to configure the project. The version number can be adjusted depending on your specific requirements or the features you plan on using.

project(MyProject): Sets the project name to "MyProject". You can rename MyProject to whatever you wish.

set(CMAKE_CXX_STANDARD 17) and set(CMAKE_CXX_STANDARD_REQUIRED True): This specifies that C++17 should be used for the project. Adjust this if you need a different C++ standard .

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build): This line sets the directory where the binary output will be placed. The CMAKE_BINARY_DIR variable automatically points to the directory where CMake is building the project (build directory in this example). The resulting executable will be placed in build/build.

include_directories(include): Adds the include directory to the list of paths to search for header files.

file(GLOB SOURCES "src/*.cpp"): This command collects all .cpp files under the src directory and stores them in the SOURCES variable. It's generally handy, but in larger projects, specifying each source file manually can prevent potential issues.

add_executable(MyExecutable ${SOURCES}): This command creates an executable target named MyExecutable using the source files collected in the SOURCES variable. Replace MyExecutable with your desired output binary name.

# Building the Project

Open a terminal  and navigate to the root of your project directory.

Create a build directory . You can accomplish this with the following command:

mkdir -p build
Navigate into the build directory:

cd build
Run CMake to configure the project:

cmake ..
Build the project:

cmake --build .
After following these steps, the built executable should be located in the build/build directory.

Remember to adapt the names and paths in the CMakeLists.txt to the specific structure and requirements of your project.