cmake_minimum_required(VERSION 3.15)
project(ApexDynamicsSim VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenMP for parallel tire/suspension calculations
find_package(OpenMP REQUIRED)

# Find Eigen3 for High-Performance Linear Algebra
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Add Include Directories
include_directories(include)

# Gather Source Files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen OpenMP::OpenMP_CXX)

# Enable aggressive compiler optimizations for real-time integration
target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native -ffast-math)
