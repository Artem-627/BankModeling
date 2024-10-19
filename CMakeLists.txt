cmake_minimum_required(VERSION 3.26.4)
project(BankModeling)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "C://Libraries/SFML/lib/cmake/SFML")
#set(CMAKE_PREFIX_PATH "/home/artem627/SQLiteCpp/vcpkg/ports/asio/")

add_executable(${PROJECT_NAME}
        main.cpp

        include/Primitives.h
        source/Primitives.cpp

        include/Time.h
        source/Time.cpp

        include/Banker.h
        source/Banker.cpp
        
        include/ClientsQueue.h
        source/ClientsQueue.cpp

        include/Bank.h
        source/Bank.cpp

        include/TimeProcessing.h
        source/TimeProcessing.cpp
        
        include/Statistics.h
        
        include/Analyzer.h
        source/Analyzer.cpp

        include/server/Server.h
        source/server/Server.cpp
)

#add_subdirectory(tests)

find_package(SFML 2.6.1 COMPONENTS network audio graphics window system REQUIRED)
find_package(Crow REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
    sfml-network
    sfml-audio
    sfml-graphics
    sfml-window
    sfml-system
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Crow::Crow
)

# Enabling tests
#enable_testing()
#add_test(NAME gtest_tests COMMAND tests/tests --gtest_output=xml:./ctest-tests.xml)
