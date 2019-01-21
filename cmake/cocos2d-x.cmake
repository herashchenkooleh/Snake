macro(fetch_cocos2d_x _download_module_path _download_root)

    set(COCOS2D_X_DOWNLOAD_ROOT ${_download_root})

    configure_file (
        ${_download_module_path}/cocos2d-x-download.cmake
        ${_download_root}/CMakeLists.txt
        @ONLY
    )

    unset(COCOS2D_X_DOWNLOAD_ROOT)

    execute_process (
        COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${_download_root}
    )

    execute_process (
        COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY ${_download_root}
    )

    add_subdirectory (
        ${_download_root}/cocos2d-x-src
        ${_download_root}/cocos2d-x-build
    )
endmacro()