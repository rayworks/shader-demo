cmake_minimum_required(VERSION 3.15)
project(OpenGL_Example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 1. Find OpenGL
find_package(OpenGL REQUIRED)

# 2. Robust GLFW detection
find_package(GLFW3 QUIET)
if(NOT GLFW3_FOUND)
    # Fallback to looking for "glfw" or using PkgConfig (common on Linux/macOS)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
endif()

# 3. Define the executable target
add_executable(prog 
    example1.cpp 
    ../comm/InitShader.cpp
)

target_include_directories(prog PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../comm
    ${GLFW_INCLUDE_DIRS} # Fallback include dir if target doesn't exist
)

# 4. Smart Linking: Corrected target checks
if(TARGET GLFW::glfw)
    target_link_libraries(prog PRIVATE GLFW::glfw OpenGL::GL)
elseif(TARGET glfw)
    target_link_libraries(prog PRIVATE glfw OpenGL::GL)
else()
    target_link_libraries(prog PRIVATE ${GLFW_LIBRARIES} OpenGL::GL)
endif()