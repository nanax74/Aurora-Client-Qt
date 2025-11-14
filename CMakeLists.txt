cmake_minimum_required(VERSION 3.16)
project(Aurora-Qt LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.10.0/mingw_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Quick Qml)

add_compile_definitions(UNICODE _UNICODE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Dist")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Dist")

add_executable(Aurora-Qt
    Source/Main.cpp
    Source/ConsoleController.cpp
    Source/ConsoleModel.cpp

    Include/ConsoleController.hpp
    Include/ConsoleModel.hpp

    UI/Qml.qrc
)

target_link_libraries(Aurora-Qt PRIVATE
    Qt6::Quick
    Qt6::Qml
)

target_include_directories(Aurora-Qt PRIVATE
    ${CMAKE_SOURCE_DIR}/Include 
)

add_custom_command(TARGET Aurora-Qt POST_BUILD
    COMMAND "D:/Qt/6.10.0/mingw_64/bin/windeployqt.exe"
            --qmldir "${CMAKE_SOURCE_DIR}/UI"
            "$<TARGET_FILE:Aurora-Qt>" > NUL
)
