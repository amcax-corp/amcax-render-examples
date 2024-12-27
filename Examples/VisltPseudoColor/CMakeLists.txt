
cmake_minimum_required (VERSION 3.12)


project ("VisltPseudoColor")

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

add_executable (VisltPseudoColor ${PROJECT_FILES} )

target_link_libraries(VisltPseudoColor PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(VisltPseudoColor PRIVATE AMCAXRender::AMCAXRender)