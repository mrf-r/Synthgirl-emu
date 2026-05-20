DIR_BUILD="build-cmake"
rm -fr $DIR_BUILD
mkdir $DIR_BUILD
cmake -S ./ -B $DIR_BUILD
cmake --build $DIR_BUILD -j
# -v