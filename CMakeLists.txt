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
    lib/olcPGEX_MiniAudio.h
    lib/clay.h
    obj/Ball.cpp
    obj/BaseObject.cpp
    obj/Bat.cpp
    obj/upgrades/BaseUpgrade.cpp
    obj/upgrades/BaseUpgrade.h
    ui/MainMenu.cpp
    ui/MainMenu.h
    ui/PauseMenu.cpp
    ui/PauseMenu.h
    ui/Hud.h
    ui/Hud.cpp
    engine/engine.h
    engine/engine.cpp
    engine/GameState.h
    engine/GameState.cpp
    engine/Clay_Renderer_PGE.h
    engine/Clay_Renderer_PGE.cpp
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


#[===[
set_target_properties(BrickBreaker PROPERTIES OUTPUT_NAME "BrickBreaker") 
message(STATUS "Looking for X11...")
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(BrickBreaker PRIVATE ${X11_LIBRARIES})

message(STATUS "looking for png...")
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(BrickBreaker PRIVATE ${PNG_LIBRARIES})

message(STATUS "looking for GL...")
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(BrickBreaker PRIVATE ${OPENGL_LIBRARIES})

TARGET_LINK_LIBRARIES(BrickBreaker PRIVATE pthread)
target_link_libraries(BrickBreaker PRIVATE stdc++fs)

]===]

include(cmake/PGE.cmake)
pge_set_emscripten_options(BrickBreaker)
