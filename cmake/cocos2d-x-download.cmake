cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(cocos2d-x-download NONE)
include(ExternalProject)

set(COCOS2D_X_SUBMODULES "") 

ExternalProject_Add (
    cocos2d-x
    SOURCE_DIR "@COCOS2D_X_DOWNLOAD_ROOT@/cocos2d-x-src"
    BINARY_DIR "@COCOS2D_X_DOWNLOAD_ROOT@/cocos2d-x-build"
    GIT_REPOSITORY https://github.com/cocos2d/cocos2d-x.git
    GIT_TAG "v3"
    GIT_SUBMODULES "${COCOS2D_X_SUBMODULES}"
    CONFIGURE_COMMAND "@COCOS2D_X_DOWNLOAD_ROOT@/cocos2d-x-src/download-deps.py"
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

unset(COCOS2D_X_SUBMODULES)