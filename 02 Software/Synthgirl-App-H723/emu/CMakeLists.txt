add_subdirectory(hwPanelEmulator)
add_subdirectory(mbwmidi)
add_subdirectory(minimalgraphics)

add_executable(Emu)

target_sources(Emu
    PRIVATE
        userpanel.c
        pmain.cpp
)

target_link_libraries(Emu
    PUBLIC
        hwPanelEmulator
        mbwmidi
        minimalgraphics
        App
)

target_compile_options(Emu
    PRIVATE
        -Wall -Wextra -Wpedantic
        -std=c11 -Wdouble-promotion
)

add_library(Emu_inc INTERFACE)
target_sources(Emu_inc
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS
        ${CMAKE_CURRENT_LIST_DIR}
    FILES
        ${CMAKE_CURRENT_LIST_DIR}/bsp.h
        ${CMAKE_CURRENT_LIST_DIR}/userpanel.h
        ${CMAKE_CURRENT_LIST_DIR}/Dac.h
        ${CMAKE_CURRENT_LIST_DIR}/Global.h
)

add_library(hwPanelEmulator_config INTERFACE)
target_sources(hwPanelEmulator_config
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS
        ${CMAKE_CURRENT_LIST_DIR}
    FILES
        ${CMAKE_CURRENT_LIST_DIR}/panel_conf.h
)