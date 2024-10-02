cmake_minimum_required(VERSION 3.29)
project(BankModeling)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
        main.cpp
)

find_package(SFML 2.6.1 COMPONENTS network audio graphics window system REQUIRED)

include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
        sfml-network
        sfml-audio
        sfml-graphics
        sfml-window
        sfml-system
)
