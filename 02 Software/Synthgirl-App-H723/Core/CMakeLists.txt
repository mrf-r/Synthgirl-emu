
add_library(App OBJECT)

target_sources(App
    PRIVATE
        Library/Controller/Controller.cpp
        Library/Lcd/lcd.cpp
)

target_include_directories(App
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Library/Controller
        # ${CMAKE_CURRENT_LIST_DIR}/Library/Dac
        # ${CMAKE_CURRENT_LIST_DIR}/Library/Global
        ${CMAKE_CURRENT_LIST_DIR}/Library/Lcd
)

# target_compile_options(App PRIVATE -Wall -Wextra -Wpedantic -Wdouble-promotion)
target_compile_options(App PRIVATE -std=c++17)
# add_compile_definitions(UNITTEST)

target_link_libraries(App
    PUBLIC
        Emu_inc
        hwPanelEmulator
        mbwmidi
        minimalgraphics
)