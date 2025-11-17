cmake_minimum_required(VERSION 3.16)
project(Aurora-Qt LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_PREFIX_PATH "D:/Qt/6.10.0/mingw_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Quick Qml)

add_compile_definitions(UNICODE _UNICODE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Dist")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Dist")

# ---- ソースとヘッダ ----

file(GLOB_RECURSE THIS_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/Source/*.cpp
    ${CMAKE_SOURCE_DIR}/Include/*.hpp
)

file(GLOB_RECURSE COMMON_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/../Common/Source/*.cpp
    ${CMAKE_SOURCE_DIR}/../Common/Include/*.hpp
)

set(THIS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Include)
set(COMMON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../Common/Include)

# ---- 実行ファイル ----

add_executable(Aurora-Qt
    ${THIS_SOURCE_FILES}
    ${COMMON_SOURCE_FILES}
    UI/Qml.qrc
)

# ---- include path ----
target_include_directories(Aurora-Qt PRIVATE
    ${THIS_INCLUDE_DIR}
    ${COMMON_INCLUDE_DIR}
)

# ---- Qt ----
target_link_libraries(Aurora-Qt PRIVATE
    Qt6::Quick
    Qt6::Qml
)

# ---- deploy ----
add_custom_command(TARGET Aurora-Qt POST_BUILD
    COMMAND "D:/Qt/6.10.0/mingw_64/bin/windeployqt.exe"
            --qmldir "${CMAKE_SOURCE_DIR}/UI"
            "$<TARGET_FILE:Aurora-Qt>" > NUL
)
