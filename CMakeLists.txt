cmake_minimum_required(VERSION 3.30)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BINARY_DIR build)
set(CMAKE_SOURCE_DIR ./)
set(EXECUTABLE_OUTPUT_PATH build)

include_directories(.)
include_directories(lib)
include_directories(obj)
include_directories(ui)
add_executable(BrickBreaker
    lib/olcPGEX_QuickGUI.h
    lib/olcPixelGameEngine.h
    lib/miniaudio.h
    lib/miniaudio_libopus.h
    lib/miniaudio_libopus.c
    lib/miniaudio_libvorbis.h
    lib/miniaudio_libvorbis.c
    lib/olcPGEX_MiniAudio.h
    lib/clay.h
    obj/Ball.cpp
    obj/BaseObject.cpp
    obj/Bat.cpp
    obj/upgrades/BaseUpgrade.cpp
    obj/upgrades/BaseUpgrade.h
    obj/upgrades/IncreaseBatWidth.h
    obj/upgrades/IncreaseBatWidth.cpp
    obj/upgrades/UpgradeFactory.h
    obj/upgrades/NewBallsUpgrade.cpp
    obj/upgrades/NewBallsUpgrade.h
    ui/MainMenu.cpp
    ui/MainMenu.h
    ui/PauseMenu.cpp
    ui/PauseMenu.h
    ui/GameOverMenu.cpp
    ui/GameOverMenu.h
    ui/Hud.h
    ui/Hud.cpp
    ui/OptionsMenu.h
    ui/OptionsMenu.cpp
    engine/engine.h
    engine/engine.cpp
    engine/GameState.h
    engine/GameState.cpp
    engine/Clay_Renderer_PGE.h
    engine/Clay_Renderer_PGE.cpp
    engine/AudioManager.h
    engine/AudioManager.cpp
    engine/guuid.h
    main.cpp
    main.h
    obj/Ball.h
    obj/BaseObject.h
    obj/BaseBrick.h
    obj/BaseBrick.cpp
    obj/Bat.h)

if (${CMAKE_CXX_COMPILER} MATCHES ".*em[+][+]")
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")
else()
   set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "BrickBreaker")
endif()

add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-g;")


if (${CMAKE_CXX_COMPILER} MATCHES ".*g[+][+]")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(OPUSFILE REQUIRED opusfile opus ogg)
  pkg_check_modules(VORBIS REQUIRED vorbisfile vorbis ogg)

  # Link against the Opusfile, Opus, and Ogg libraries
  target_link_libraries(BrickBreaker PUBLIC ${OPUSFILE_LIBRARIES})

  # Add include directories
  target_include_directories(BrickBreaker PUBLIC ${OPUSFILE_INCLUDE_DIRS})

  # 4. Link the executable with the found libraries
  target_link_libraries(BrickBreaker PUBLIC ${VORBIS_LIBRARIES})

  # 5. Add the necessary include directories
  target_include_directories(BrickBreaker PUBLIC ${VORBIS_INCLUDE_DIRS})
endif()

include(cmake/PGE.cmake)
pge_set_emscripten_options(BrickBreaker)
