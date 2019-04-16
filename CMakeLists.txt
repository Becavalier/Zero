cmake_minimum_required (VERSION 3.11)

project (Zero)

set (CMAKE_VERBOSE_MAKEFILE "OFF")
set (CMAKE_CXX_STANDARD "11")
set (STATE $ENV{CMAKE_TARGET})

# set folders;
set (N_SOURCE_SRC "src")
set (N_OUTPUT_SRC "dist")
set (N_LIB_SRC "jerryscript/build")

# set headers include path;
include_directories(${N_LIB_SRC} jerryscript/jerry-core/include jerryscript/jerry-ext/include ${N_SOURCE_SRC}/cppcodec)

# conditional compiling;
if (STATE STREQUAL WASM) 
    set (OUTPUT "zero.output")
    ADD_DEFINITIONS (-DWASM)
    set (CMAKE_CXX_FLAGS " \
    -O3 \
    -s WASM=1 \
    --closure 1 \
    --llvm-lto 1 \
    -fno-rtti \
    -s NO_EXIT_RUNTIME=1 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s ASSERTIONS=0 \
    -s NO_FILESYSTEM=1 \
    -s MODULARIZE=1 \
    -s EXPORT_NAME=\"Zero\" \
    ${CMAKE_CXX_FLAGS} \
    ")
else()
    set (OUTPUT "zero")
    set (CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")
endif()

set (EXECUTABLE_OUTPUT_PATH ${N_OUTPUT_SRC})

# resolve source files;
aux_source_directory (${N_SOURCE_SRC} DIR_SRCS)   
aux_source_directory (${N_LIB_SRC} DIR_SRCS)       

add_library(ext STATIC IMPORTED)
set_target_properties(ext PROPERTIES IMPORTED_LOCATION
    ${N_LIB_SRC}/lib/libjerry-ext.a)

# compiling target;
add_executable (${OUTPUT} ${DIR_SRCS})

target_link_libraries (${OUTPUT} ext)
