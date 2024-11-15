# CMakeLists.txt

# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# # Set the project name
project(ToolLogQt)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17) # Use C++17, adjust as needed (11, 14, 20, etc.)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Ensure standard is required
set(CMAKE_CXX_EXTENSIONS OFF) # Disable compiler-specific extensions

# Add the 'inc' directory to the include path
include_directories(
    ${CMAKE_SOURCE_DIR}/controller/inc
    ${CMAKE_SOURCE_DIR}/model/inc
    ${CMAKE_SOURCE_DIR}/view/inc
    ${CMAKE_SOURCE_DIR}/util/inc
)

# Find all source files in the src directory
file(GLOB MAIN_SOURCE 
    "model/**/*.cpp"
    "controller/**/*.cpp"
    "view/**/*.cpp"
    "util/**/*.cpp"
    "ui-test.cpp"
)

# Create the executable
add_executable(${PROJECT_NAME} ${MAIN_SOURCE})
