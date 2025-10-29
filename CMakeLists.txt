cmake_minimum_required(VERSION 3.16)
project(QtApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.10.0/mingw_64/lib/cmake")

set(LIBRARY_DIR "D:/Nyan/C++/Install")

find_package(Qt6 REQUIRED COMPONENTS Quick Qml)

add_compile_definitions(UNICODE _UNICODE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Dist")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Dist")

add_executable(QtApp
    Source/Main.cpp
    UI/Qml.qrc
)

target_link_libraries(QtApp PRIVATE
    Qt6::Quick
    Qt6::Qml
)

target_include_directories(QtApp PRIVATE ${LIBRARY_DIR}/include)
target_link_libraries(QtApp PRIVATE ${LIBRARY_DIR}/lib/libProgress.a)

add_custom_command(TARGET QtApp POST_BUILD
    COMMAND "D:/Qt/6.10.0/mingw_64/bin/windeployqt.exe"
            --qmldir "${CMAKE_SOURCE_DIR}/UI"
            "$<TARGET_FILE:QtApp>" > NUL
)
