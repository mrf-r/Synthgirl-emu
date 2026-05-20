cmake_minimum_required(VERSION 3.23)
project(synthgirl)

# add_compile_options(-gdwarf-3)
# add_link_options(-gdwarf-3)

add_subdirectory(emu)
add_subdirectory(Core)


# to read
# https://cmake.org/cmake/help/latest/genindex.html
# https://github.com/FreeRTOS/FreeRTOS-Kernel/blob/main/CMakeLists.txt
# https://github.com/SynthstromAudible/DelugeFirmware/blob/community/src/OSLikeStuff/CMakeLists.txt
# https://github.com/nonlinear-labs-dev/nl-firmware/blob/main/projects/epc/audio-engine/CMakeLists.txt
# https://github.com/raspberrypi/pico-sdk - some overcomplicated stuff that doesn't work

# TODO: install
# https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
# !!!!!!!!!!!!!!
