cmake_minimum_required(VERSION 3.21)
project(GuessThePerson LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)     # автоматически обработает Q_OBJECT
set(CMAKE_AUTORCC ON)     # автоматически обработает resources.qrc

# Минимальная версия Qt — 6.10
find_package(Qt6 6.10 REQUIRED COMPONENTS Widgets)

# Автоматически собираем все .cpp и .h в корне проекта.
# CONFIGURE_DEPENDS — чтобы новые файлы подхватывались без перезапуска cmake.
file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

qt_add_executable(GuessThePerson
    ${PROJECT_SOURCES}
    resources.qrc
)

target_link_libraries(GuessThePerson PRIVATE Qt6::Widgets)