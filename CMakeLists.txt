project(TowerDefense)

cmake_minimum_required(VERSION 3.7.0)

set(SDL_INCLUDE_DIR "/usr/include/SDL2")
set(SDL_LIBRARY "SDL2")
include(FindSDL)

if(SDL_FOUND)  
  message(STATUS "SDL FOUND")
endif()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(SDL2_TTF "SDL2_ttf")
add_executable(${PROJECT_NAME} apps/main.cpp src/game.cpp src/assetsmanager.cpp src/instances.cpp src/grid.cpp src/menu.cpp src/widget.cpp)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2mixer REQUIRED SDL2_mixer)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2mixer_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2} ${SDL2_TTF})
