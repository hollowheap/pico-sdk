if (NOT TARGET pico_base_headers)
    pico_add_library(pico_base NOFLAG)
    target_include_directories(pico_base_headers SYSTEM INTERFACE include ${CMAKE_BINARY_DIR}/generated/pico_base)

    # PICO_BUILD_DEFINE: PICO_BOARD, Name of board, type=string, default=CMake PICO_BOARD variable, group=pico_base
    target_compile_definitions(pico_base_headers INTERFACE
            PICO_BOARD="${PICO_BOARD}")

    # PICO_BUILD_DEFINE: PICO_PLATFORM_STRING, Name of platform, type=string, default=CMake PICO_PLATFORM variable, group=pico_base
    target_compile_definitions(pico_base_headers INTERFACE
            PICO_PLATFORM_STRING="${PICO_PLATFORM}")

    foreach(override ${PICO_BOARD_CMAKE_OVERRIDES})
        target_compile_definitions(pico_base_headers INTERFACE
                ${override}=${${override}})
    endforeach()

    target_link_libraries(pico_base_headers INTERFACE pico_platform_headers)

    # C99 builds: force-include the static_assert fallback in C TUs only.
    # The header itself no-ops on C11+, C++ and assembler.
    target_compile_options(pico_base_headers INTERFACE
            $<$<COMPILE_LANGUAGE:C>:-include pico/c99_static_assert.h>)

    list(APPEND PICO_SDK_POST_LIST_FILES ${CMAKE_CURRENT_LIST_DIR}/generate_config_header.cmake)
    pico_promote_common_scope_vars()
endif()