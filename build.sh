# cleanup;
make clean
rm -rf ./build
rm -rf CMakeCache.txt

echo $CMAKE_CXX_COMPILER_ID
if [ "$1" = "--native" ]
then
    export CMAKE_TARGET="NATIVE"
    sudo cmake .
    sudo make
else
    export CMAKE_TARGET="WASM"
    sudo emconfigure cmake .
    sudo emmake make VERBOSE=1
fi