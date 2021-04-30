cmake_minimum_required(VERSION 2.8)

project(Pencere)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
            ${PROJECT_SOURCE_DIR}/kutuphane.cpp
            ${PROJECT_SOURCE_DIR}/main.cpp
            ${PROJECT_SOURCE_DIR}/glad.c
            )

set(PROJECT_HEADERS 
            ${PROJECT_INCLUDE_DIR}/kutuphane.hpp
)

set(glfw3_DIR ${PROJECT_DIR}/../../Dependencies/GLFW/lib/cmake/glfw3)
    
set(GLM_INCLUDE_DIR ${PROJECT_DIR}/../../Dependencies)

set(PROJECT_INCLUDE_DIR 
    ${PROJECT_DIR}/include
    ${GLM_INCLUDE_DIR}    
)

find_package(glfw3 3.2.1 REQUIRED)

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)