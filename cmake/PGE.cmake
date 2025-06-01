
if (${CMAKE_CXX_COMPILER} MATCHES ".*em[+][+]")
    set(PGE_USE_EMSCRIPTEN TRUE)
else()
    set(PGE_USE_EMSCRIPTEN FALSE)
endif()

if (PGE_USE_EMSCRIPTEN)
    # Compile to HTML5
    set(CMAKE_EXECUTABLE_SUFFIX .html)
    # find_package(Emscripten REQUIRED)

    # This is genuinely such a pain in the ass but we had to compile opus support into emscripten manually
    # and I could not find a way for CMake to find these paths without mangling them, so they're hardcoded
    # not really ideal tbh but i'm not smart enough (yet) to find a more elegant solution around this problem
    find_library(OPUS_STATIC_LIB NAMES opus PATHS "/home/jundy/emsdk_libs/install/lib" NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
    find_library(OPUSFILE_STATIC_LIB NAMES opusfile PATHS "/home/jundy/emsdk_libs/install/lib" NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
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
        set(PGE_LINKER_OPTIONS -sALLOW_MEMORY_GROWTH=1 -sASSERTIONS=1 -sSTACK_SIZE=131072 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sUSE_LIBPNG=1 -sUSE_ZLIB=1 -sUSE_VORBIS=1 -sUSE_OGG=1 --emrun)
        target_link_options(${project_name} PRIVATE -sEXCEPTION_CATCHING_ALLOWED=[compile+link])
        target_link_options(${project_name} PRIVATE -sEXPORTED_RUNTIME_METHODS=["HEAPF32"])

        set(OPUSFILE_LIB "/home/jundy/emsdk_libs/install/include/opus")
        target_include_directories(BrickBreaker PUBLIC ${OPUSFILE_LIB})
        
        target_link_libraries(BrickBreaker PUBLIC
          ${OPUSFILE_STATIC_LIB}
          ${OPUS_STATIC_LIB}
          )

        if (PGE_USE_EMSCRIPTEN)
      target_link_options(${project_name} PRIVATE ${PGE_LINKER_OPTIONS} --preload-file ${PGE_ASSET_FOLDER})
        else()
            target_link_options(${project_name} PRIVATE ${PGE_LINKER_OPTIONS})
        endif()

        if (PGE_USE_SHELL)
          target_link_options(${project_name} PRIVATE --shell-file ${CMAKE_SOURCE_DIR}/cmake/shell_minimal.html)
        else()
          target_link_options(${project_name} PRIVATE --shell-file ${CMAKE_SOURCE_DIR}/cmake/template.html)
        endif()

    else()
        if (UNIX)
      target_link_libraries(${project_name} PRIVATE -ggdb -lX11 -lGL -lpthread -lpng -ldl -lm -lstdc++ -lopusfile -lopus -logg)
        endif (UNIX)
    endif()
endfunction()
