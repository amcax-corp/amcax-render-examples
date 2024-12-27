cmake_minimum_required(VERSION 3.16)
project(Coordinate)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(AMCAXRender )
find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

file(GLOB ALL_UI_FILES *.ui)
file(GLOB ALL_FILES *.cpp *.h)

add_executable(${PROJECT_NAME} ${ALL_UI_FILES} ${ALL_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE AMCAXRender::AMCAXRender)





