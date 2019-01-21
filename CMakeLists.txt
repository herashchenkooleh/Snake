cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Snake CXX)

#add_definitions(-DCC_SPRITE_DEBUG_DRAW=1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(cmake/cocos2d-x.cmake)

fetch_cocos2d_x(${PROJECT_SOURCE_DIR}/cmake ${PROJECT_BINARY_DIR}/cocos2d-x)

add_subdirectory(game)

set_target_properties (cpp-empty-test PROPERTIES FOLDER tests)
set_target_properties (cpp-tests PROPERTIES FOLDER tests)
set_target_properties (js-tests PROPERTIES FOLDER tests)
set_target_properties (lua-empty-test PROPERTIES FOLDER tests)
set_target_properties (lua-tests PROPERTIES FOLDER tests)
