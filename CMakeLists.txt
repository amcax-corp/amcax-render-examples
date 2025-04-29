# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)
project(Render-example)
# 指定 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Json_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Packages/nlohmann_json/")

list(APPEND CMAKE_PREFIX_PATH ${AMCAX_DIR} ${AMCAXRender_PATH} ${Json_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 获取当前目录下的所有文件和文件夹
file(GLOB ALL_ENTRIES "${CMAKE_CURRENT_SOURCE_DIR}/Examples/*")

# 遍历每个条目
foreach(ENTRY ${ALL_ENTRIES})
    if(IS_DIRECTORY ${ENTRY})
        #message(STATUS "Found directory: ${ENTRY}")
        #add_subdirectory(${ENTRY})

        file(GLOB SUB_ENTRIES "${ENTRY}/*")
        foreach(sub ${SUB_ENTRIES})
            if(IS_DIRECTORY ${sub})
                message(STATUS "Found directory: ${sub}")
                add_subdirectory(${sub}) 
            endif()
        endforeach()
    endif()
endforeach()


