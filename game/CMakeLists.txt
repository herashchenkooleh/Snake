cmake_minimum_required(VERSION 3.6)

set(APP_NAME Snake)

project(${APP_NAME})

file(GLOB SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB INC_FILES ${CMAKE_CURRENT_LIST_DIR}/inc/*.hpp)

file(GLOB SNAKE_SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/Snake/*.cpp)
file(GLOB SNAKE_INC_FILES ${CMAKE_CURRENT_LIST_DIR}/inc/Snake/*.h)

source_group("Header Files\\Snake Include Files" FILES ${SNAKE_INC_FILES})
source_group("Source Files\\Snake Source Files" FILES ${SNAKE_SRC_FILES})

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
)

set(APP_DEBUG_RES_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}/Debug/Resources")
set(APP_RELEASE_RES_DIR "${CMAKE_BINARY_DIR}/bin/${APP_NAME}/Release/Resources")

add_executable(${APP_NAME} WIN32 ${SRC_FILES} ${INC_FILES} ${SNAKE_SRC_FILES} ${SNAKE_INC_FILES})

target_include_directories (
    Snake
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(Snake cocos2d)

setup_cocos_app_config(${APP_NAME})
cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_DEBUG_RES_DIR}/..)
cocos_copy_res(COPY_TO ${APP_DEBUG_RES_DIR} FOLDERS ${GAME_RES_FOLDER})

cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_RELEASE_RES_DIR}/..)
cocos_copy_res(COPY_TO ${APP_RELEASE_RES_DIR} FOLDERS ${GAME_RES_FOLDER})