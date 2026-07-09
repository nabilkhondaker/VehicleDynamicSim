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

# Gather Core Source Files (Excluding Tests)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define Main Executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen OpenMP::OpenMP_CXX)
target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native -ffast-math)

# ==========================================
# Google Test Integration (The Missing Glue)
# ==========================================
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Build Test Executable
add_executable(ApexSimTests tests/test_pacejka.cpp tests/test_integration.cpp)
target_include_directories(ApexSimTests PRIVATE include)
target_link_libraries(ApexSimTests PRIVATE 
    Eigen3::Eigen 
    gtest_main 
    # We need to link the object files from src/ to the tests, 
    # so in a real massive project, we'd make src/ a STATIC library.
)

include(GoogleTest)
gtest_discover_tests(ApexSimTests)
