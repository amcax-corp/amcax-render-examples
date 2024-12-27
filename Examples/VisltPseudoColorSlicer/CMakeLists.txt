
cmake_minimum_required (VERSION 3.12)


project ("VisltPseudoColorSlicer")

find_package(AMCAXRender REQUIRED) 
find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_definitions(-DUSE_AMCAX_KERNEL)


set(PROJECT_FILES
    main.cpp
    VisltDemo.cpp
    VisltDemo.ui 
)

add_executable (VisltPseudoColorSlicer ${PROJECT_FILES} )

target_link_libraries(VisltPseudoColorSlicer PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(VisltPseudoColorSlicer PRIVATE AMCAXRender::AMCAXRender)