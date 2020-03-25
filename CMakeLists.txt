cmake_minimum_required(VERSION 3.17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Steganography VERSION 1.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

set(SOURCE_LIST
    ".gitignore"
    "CMakeLists.txt"
    "LICENSE"
    "README.md"
    "src/Main.cpp"
    "src/Steganography.cpp"
    "src/Steganography.hpp"
    )

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME} 
                      ${OpenCV_LIBS}
                     )
