cmake_minimum_required(VERSION 3.26)
project(qt_webengine_load_img_test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        WebEngineWidgets
        REQUIRED)

add_executable(test main.cpp)
target_link_libraries(test
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::WebEngineWidgets
)

