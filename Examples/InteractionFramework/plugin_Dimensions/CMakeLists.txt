cmake_minimum_required(VERSION 3.16)
project(plugin_Dimensions)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH ${AMCAXRender_PATH})
find_package(AMCAXRender )

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

list(APPEND CMAKE_PREFIX_PATH ${Json_PATH})
find_package(nlohmann_json 3.11.3 REQUIRED)

file(GLOB ALL_UI_FILES *.ui)
file(GLOB ALL_FILES *.cpp *.h)

add_executable(${PROJECT_NAME} ${ALL_UI_FILES} ${ALL_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE AMCAXRender::AMCAXRender)





