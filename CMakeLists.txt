cmake_minimum_required(VERSION 3.16)
project(liquid-sim LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)



set(PROJECT_HEADERS 
    include/game.h
    include/grid.h
    include/block.h
    include/material-type.h
    include/ui.h
)

set(PROJECT_SOURCES 
    src/main.cpp
    src/game.cpp
    src/grid.cpp
    src/block.cpp
    src/ui.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE include)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_link_libraries(liquid-sim PRIVATE sfml-graphics)
target_link_libraries(liquid-sim PRIVATE sfml-audio)
target_compile_features(liquid-sim PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET liquid-sim
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:liquid-sim>
        VERBATIM)
endif()

install(TARGETS liquid-sim)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
