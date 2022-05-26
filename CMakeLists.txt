cmake_minimum_required(VERSION 3.0.0)
project(smallWiener LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/BuildScripts)

if(NOT GENERATOR_IS_MULTI_CONFIG AND (NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL ""))
    message(AUTHOR_WARNING "No build type described. Defauling to Release.")

    set(CMAKE_BUILD_TYPE Release)
endif()

set(SOURCES_DIR         ${CMAKE_CURRENT_LIST_DIR}/Sources)
set(THIRDPARTY_FOLDER   ${CMAKE_CURRENT_LIST_DIR}/ThirdParty)

find_package(godot-cpp REQUIRED)

add_library(smallWiener SHARED
    ${SOURCES_DIR}/PlayerCharacter.hpp
    ${SOURCES_DIR}/TapBuffer.hpp

    ${SOURCES_DIR}/PlayerCharacter.cpp
    ${SOURCES_DIR}/TapBuffer.cpp

    ${SOURCES_DIR}/Main.cpp
)

target_include_directories(smallWiener PRIVATE ${GODOTCPP_INCLUDE_DIRS})
target_link_libraries(smallWiener PRIVATE ${GODOTCPP_LIBRARIES})

if(NOT (WIN32 OR APPLE OR UNIX))
    message(FATAL_ERROR "This platform isn't supported yet.")
endif()

set_target_properties(smallWiener PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

if(GENERATOR_IS_MULTI_CONFIG)
    set_target_properties(smallWiener PROPERTIES OUTPUT_NAME smallWiener.$<LOWER_CASE:$<CONFIG>>)
else()
    set_target_properties(smallWiener PROPERTIES OUTPUT_NAME smallWiener.$<LOWER_CASE:${CMAKE_BUILD_TYPE}>)
endif()

file(TOUCH ${CMAKE_BINARY_DIR}/.gdignore)

# TODO: generate gdnative at runtime
