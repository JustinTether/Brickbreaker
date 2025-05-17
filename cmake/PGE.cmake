
if (${CMAKE_CXX_COMPILER} MATCHES ".*em[+][+]")
    set(PGE_USE_EMSCRIPTEN TRUE)
    message("use emscripten true")
else()
    set(PGE_USE_EMSCRIPTEN FALSE)
endif()

if (PGE_USE_EMSCRIPTEN)
    # Compile to HTML5
    set(CMAKE_EXECUTABLE_SUFFIX .html)
    # find_package(Emscripten REQUIRED)
endif()


# Asset folder
set(PGE_ASSET_FOLDER "${CMAKE_SOURCE_DIR}/assets")

# Copy the assets folder to the binary if it exists
if (EXISTS ${PGE_ASSET_FOLDER} AND IS_DIRECTORY ${PGE_ASSET_FOLDER})
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif()

set(CMAKE_CXX_STANDARD 20)


# Sets the needed options for a specifig PGE target
#
# Usage: pge_set_emscripten_options(target)
function(pge_set_emscripten_options project_name)
    if (PGE_USE_EMSCRIPTEN)
        set(PGE_LINKER_OPTIONS -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=131072 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sUSE_LIBPNG=1 --emrun)
        target_link_options(${project_name} PRIVATE -sEXCEPTION_CATCHING_ALLOWED=[compile+link])
        target_link_options(${project_name} PRIVATE -sEXPORTED_RUNTIME_METHODS=["HEAPF32"])
        if (PGE_INCLUDE_ASSETS)
      target_link_options(${project_name} PRIVATE ${PGE_LINKER_OPTIONS} --preload-file ${PGE_ASSET_FOLDER})
        else()
            target_link_options(${project_name} PRIVATE ${PGE_LINKER_OPTIONS})
        endif()

        if (PGE_USE_SHELL)
          target_link_options(${project_name} PRIVATE --shell-file ${CMAKE_SOURCE_DIR}/cmake/shell_minimal.html)
        else()
          target_link_options(${project_name} PRIVATE --shell-file ${CMAKE_SOURCE_DIR}/cmake/template.html)
        endif()

        # target_link_libraries(${project_name} PRIVATE emscripten::libpng)
    else()
        if (UNIX)
      target_link_libraries(${project_name} PRIVATE -lX11 -lGL -lpthread -lpng -lstdc++fs -ldl -lm -lstdc++)
        endif (UNIX)
    endif()
endfunction()
