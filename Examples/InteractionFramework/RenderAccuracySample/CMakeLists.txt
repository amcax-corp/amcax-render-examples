cmake_minimum_required(VERSION 3.16)
project(RenderAccuracySample)

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

set(PROJECT_FILES
    main.cpp
    Mainwindow.cpp
    Mainwindow.h
    RenderSetting.ui
)

set(STEP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../../resources/accuracy_sample.step")

add_executable(${PROJECT_NAME} ${PROJECT_FILES} )

target_link_libraries(${PROJECT_NAME} PRIVATE ${AMCAX_components})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE AMCAXRender::AMCAXRender)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${STEP_FILE} $<TARGET_FILE_DIR:${PROJECT_NAME}> 
)