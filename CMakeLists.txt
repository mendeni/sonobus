elseif (WIN32)
    list (APPEND HEADER_INCLUDES deps/windows ../asiosdk/common)
    list (APPEND PlatSourceFiles  Source/CrossPlatformUtilsWindows.cpp)

    # Add liblo headers and library path
    list(APPEND HEADER_INCLUDES deps/windows/liblo/include)
    list(APPEND LIB_PATHS deps/windows/liblo/lib)

    message (STATUS "Win generator platform is: ${CMAKE_VS_PLATFORM_NAME}" )
    if ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        list (APPEND LIB_PATHS
            $<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/Debug32>
            $<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/Release32>
        )
    else()
        list (APPEND LIB_PATHS
            $<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/Debug>
            $<$<CONFIG:Release>:${CMAKE_CURRENT_SOURCE_DIR}/deps/windows/Release>
        )
    endif()

    list (APPEND PLAT_COMPILE_DEFS
        _USE_MATH_DEFINES
        WINVER=0x0601
        _WIN32_WINNT=0x0601)

    # Indicate linking with liblo
    target_link_libraries("${target_name}" PRIVATE lo)
endif()