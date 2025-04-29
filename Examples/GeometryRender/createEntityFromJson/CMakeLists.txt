cmake_minimum_required(VERSION 3.16)
project(createEntityFromJson)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_definitions(-DUSE_AMCAX_KERNEL)

set(AMCAX_components AMCAXCommon AMCAXPart AMCAXStep AMCAXOCCTIO)
find_package(AMCAXCommon REQUIRED) 
find_package(AMCAXStep REQUIRED)
find_package(AMCAXPart REQUIRED) 
find_package(AMCAXOCCTIO REQUIRED) 


list(APPEND CMAKE_PREFIX_PATH ${AMCAXRender_PATH})
find_package(AMCAXRender )

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

list(APPEND CMAKE_PREFIX_PATH ${Json_PATH})
find_package(nlohmann_json 3.11.3 REQUIRED)

file(GLOB ALL_UI_FILES *.ui)
file(GLOB ALL_FILES *.cpp *.h)

add_executable(${PROJECT_NAME} ${ALL_UI_FILES} ${ALL_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${AMCAX_components})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE AMCAXRender::AMCAXRender)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)