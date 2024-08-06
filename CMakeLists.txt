cmake_minimum_required(VERSION 3.0.0)
project(SFML_test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

include(CTest)
enable_testing()

include_directories(.)

add_library(game 
    src/Vec2.cpp
)

add_executable(SFML_test src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    game
    sfml-graphics 
    sfml-window 
    sfml-system 
    sfml-audio
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)