# MINGW_PACKAGE_PREFIX=mingw-w64-x86_64
# additional libs for emulators ----------------------------
pacman -S --noconfirm \
$MINGW_PACKAGE_PREFIX-gcc \
$MINGW_PACKAGE_PREFIX-cmake \
$MINGW_PACKAGE_PREFIX-SDL2 \
$MINGW_PACKAGE_PREFIX-libserialport \
$MINGW_PACKAGE_PREFIX-portaudio \
$MINGW_PACKAGE_PREFIX-portmidi \
