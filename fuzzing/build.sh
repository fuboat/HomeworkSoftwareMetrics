#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd "$SCRIPT_DIR" || exit 1

git submodule update --init

mkdir -p build

which gcc
which g++
which cmake

#################
## build tools ##
#################

build_afl() {
    (
        cd build
        cp ../tools/1_afl/  ./ -r
        cd ./1_afl/
        CC=gcc CXX=g++ make
    )
}

build_mopt() {
    (
        cd build
        cp ../tools/2_mopt/ ./ -r
        cd ./2_mopt/MOpt
        CC=gcc CXX=g++ make
    )
}

build_libzafl() {
    (
        cd build
        cp ../tools/3_libzafl/ ./ -r
        cd 3_libzafl
        apt -y install scons
    )
}

####################
## build projects ##
####################

build_sqlite() {
    (
        mkdir -p build/1_sqlite
        cd build/1_sqlite
        CC=$(pwd)/../1_afl/afl-gcc ../../projectFiles/1_sqlite/configure --disable-shared
        make -j10
    )
}

build_libpng() {
    (
        mkdir -p build/2_libpng
        cd build/2_libpng
        CC=$(pwd)/../1_afl/afl-gcc CXX=$(pwd)/../1_afl/afl-g++ ../../projectFiles/2_libpng/configure --disable-shared
        make -j10
    )
}

build_yaml-cpp() {
    (
        mkdir -p build/3_yaml-cpp
        cd build/3_yaml-cpp
        CC=$(pwd)/../1_afl/afl-gcc CXX=$(pwd)/../1_afl/afl-g++ cmake ../../projectFiles/3_yaml-cpp/ -DBUILD_SHARED_LIBS=OFF
        make -j10
    )
}

build_libmpeg2() {
    (
        mkdir -p build/4_libmpeg2
        cd build/4_libmpeg2
        CC=$(pwd)/../1_afl/afl-gcc CXX=$(pwd)/../1_afl/afl-g++ cmake ../../projectFiles/4_libmpeg2/ -DBUILD_SHARED_LIBS=OFF
        make -j10
    )
}

build_libpostal() {
    (
        mkdir -p build/5_libpostal
        cd build/5_libpostal
        cp -r ../../projectFiles/5_libpostal/* ./
        ./bootstrap.sh
        CC=$(pwd)/../1_afl/afl-gcc CXX=$(pwd)/../1_afl/afl-g++ ./configure
        make -j10
    )
}

build_cJSON() {
    (
        mkdir -p build/6_cJSON
        cd build/6_cJSON
        CC=$(pwd)/../1_afl/afl-gcc CXX=$(pwd)/../1_afl/afl-g++ cmake ../../projectFiles/6_cJSON/ -DBUILD_SHARED_LIBS=OFF
        make -j10
    )
}

# build_TheAlgorithmsC() {
#     (
#         mkdir -p build/7_TheAlgorithmsC
#         cd build/7_TheAlgorithmsC
#         CC=$(pwd)/../1_afl/afl-gcc CXX=$(pwd)/../1_afl/afl-g++ cmake ../../projectFiles/7_TheAlgorithmsC/ -DBUILD_SHARED_LIBS=OFF
#         make -j10
#     )
# }

build_spdlog() {
    (
        mkdir -p build/8_spdlog
        cd build/8_spdlog
        CC=$(pwd)/../1_afl/afl-gcc CXX=$(pwd)/../1_afl/afl-g++ cmake ../../projectFiles/8_spdlog/ -DBUILD_SHARED_LIBS=OFF
        make -j10
    )
}

build_iostream() {
    true

    # (
    #     mkdir -p build/9_iostream
    #     cd build/9_iostream
    #     ../../projectFiles/9_iostream/configure --enable-languages=c,c++ --disable-multilib
    #     make -j10
    #     make install DESTDIR="$(pwd)/bin"
    # )

    # (
    #     mkdir build/1_afl_gcc13
    #     cp tools/1_afl/*  ./build/1_afl_gcc13 -r
    #     cd build/1_afl_gcc13
    #     CC=$(pwd)/../9_iostream/bin/usr/local/bin/gcc CXX=$(pwd)/../9_iostream/bin/usr/local/bin/g++ make
    # )

    # (
    #     cd build/9_iostream/libcpp
    #     CC=$(pwd)/../../1_afl_gcc13/afl-gcc \
    #     CXX=$(pwd)/../../1_afl_gcc13/afl-g++ \
    #     ../../../projectFiles/9_iostream/libstdc++-v3/configure --srcdir=../../../projectFiles/9_iostream/libstdc++-v3 --cache-file=./config.cache --disable-shared --disable-multilib --enable-languages=c,c++,fortran,lto,objc --program-transform-name=s,y,y, --disable-option-checking --with-target-subdir=x86_64-pc-linux-gnu --build=x86_64-pc-linux-gnu --host=x86_64-pc-linux-gnu --target=x86_64-pc-linux-gnu --disable-intermodule --enable-checking=yes,types --disable-coverage --enable-languages=c,c++,lto --disable-build-format-warnings
    #     AFL_CC="$(pwd)"/../bin/usr/local/bin/gcc
    #     AFL_CXX="$(pwd)"/../bin/usr/local/bin/g++ 
    #     export AFL_CC
    #     export AFL_CXX
    #     make -j10
    # )
    # #     cd libcpp
    # #     rm -rf ./*
    # #     CC=/mnt/jingzhou_workspace/softwareMetrics/fuzzing/build/9_iostream/bin/usr/local/bin/gcc CXX=/mnt/jingzhou_workspace/softwareMetrics/fuzzing/build/9_iostream/bin/usr/local/bin/g++ /mnt/jingzhou_workspace/softwareMetrics/fuzzing/projectFiles/9_iostream/libstdc++-v3/configure --srcdir=../../../../projectFiles/9_iostream/libstdc++-v3 --cache-file=./config.cache --disable-shared --disable-multilib --enable-languages=c,c++,fortran,lto,objc --program-transform-name=s,y,y, --disable-option-checking --with-target-subdir=x86_64-pc-linux-gnu --build=x86_64-pc-linux-gnu --host=x86_64-pc-linux-gnu --target=x86_64-pc-linux-gnu --disable-intermodule --enable-checking=yes,types --disable-coverage --enable-languages=c,c++,lto --disable-build-format-warnings
    # # )
}

build_libqalculate() {
    (
        mkdir -p build/X_libqalculate
        cd build/X_libqalculate
        cp ../../projectFiles/X_libqalculate/* ./ -r
        ./autogen.sh
        CC=$(pwd)/../1_afl/afl-gcc CXX=$(pwd)/../1_afl/afl-g++ ./configure --disable-shared
        make -j10
    )
}

######################
## build fuzz target #
######################

build_1_sqlite_drivers() {
    (
        mkdir -p fuzzTargets/1_sqlite
        cd fuzzTargets/1_sqlite
        ../../build/1_afl/afl-g++ ../../drivers/1_sqlite/driver_1.cpp -o ./driver_1 -static ../../build/1_sqlite/.libs/libsqlite3.a -pthread -ldl
        ../../build/1_afl/afl-g++ ../../drivers/1_sqlite/driver_2.cpp -o ./driver_2 -static ../../build/1_sqlite/.libs/libsqlite3.a -pthread -ldl
    )
}

build_2_libpng_drivers() {
    (
        mkdir -p fuzzTargets/2_libpng
        cd fuzzTargets/2_libpng
        ../../build/1_afl/afl-g++ ../../drivers/2_libpng/driver_1.cpp -o ./driver_1 ../../build/2_libpng/.libs/libpng16.a -lz -static
        ../../build/1_afl/afl-g++ ../../drivers/2_libpng/driver_2.cpp -o ./driver_2 ../../build/2_libpng/.libs/libpng16.a -lz -static
    )
}

build_3_yaml-cpp_drivers() {
    (
        mkdir -p fuzzTargets/3_yaml-cpp
        cd fuzzTargets/3_yaml-cpp
        ../../build/1_afl/afl-g++ -I../../projectFiles/3_yaml-cpp/include/  ../../drivers/3_yaml-cpp/driver_1.cpp -o ./driver_1 ../../build/3_yaml-cpp/libyaml-cpp.a -static
        ../../build/1_afl/afl-g++ -I../../projectFiles/3_yaml-cpp/include/  ../../drivers/3_yaml-cpp/driver_2.cpp -o ./driver_2 ../../build/3_yaml-cpp/libyaml-cpp.a -static
    )
}

build_4_libmpeg2() {
    (
        mkdir -p fuzzTargets/4_libmpeg2
        cd fuzzTargets/4_libmpeg2
        cp ../../projectFiles/4_libmpeg2/test/decoder/main.c /tmp/libmpeg2_main.c
        sed -i "s/int main(/int libmpeg2_main(/" /tmp/libmpeg2_main.c
        ../../build/1_afl/afl-gcc -DMD5_DISABLE -c -I../../projectFiles/4_libmpeg2/common -I../../projectFiles/4_libmpeg2/decoder /tmp/libmpeg2_main.c -o ./driver.o
        ../../build/1_afl/afl-g++ -I../../projectFiles/4_libmpeg2/common -I../../projectFiles/4_libmpeg2/decoder ../../drivers/4_libmpeg2/driver_1.cpp -o driver_1 ./driver.o ../../build/4_libmpeg2/libmpeg2dec.a -pthread -static
        ../../build/1_afl/afl-g++ -I../../projectFiles/4_libmpeg2/common -I../../projectFiles/4_libmpeg2/decoder ../../drivers/4_libmpeg2/driver_2.cpp -o driver_2 ./driver.o ../../build/4_libmpeg2/libmpeg2dec.a -pthread -static
        # ../../build/1_afl/afl-g++ -I../../projectFiles/4_libmpeg2/common -I../../projectFiles/4_libmpeg2/decoder ../../drivers/4_libmpeg2/driver_2.cpp -o driver_2 ../../projectFiles/4_libmpeg2/fuzzer/mpeg2_dec_fuzzer.cpp ../../build/4_libmpeg2/libmpeg2dec.a -pthread -static
    )
}

build_5_libpostal() {
    (
        mkdir -p fuzzTargets/5_libpostal
        cd fuzzTargets/5_libpostal
        ../../build/1_afl/afl-g++ ../../drivers/5_libpostal/driver_1.cpp ../../build/5_libpostal/src/.libs/libpostal.a -o driver_1 -static
        ../../build/1_afl/afl-g++ ../../drivers/5_libpostal/driver_2.cpp ../../build/5_libpostal/src/.libs/libpostal.a -o driver_2 -static
    )
}

build_6_cJSON() {
    (
        mkdir -p fuzzTargets/6_cJSON
        cd fuzzTargets/6_cJSON
        ../../build/1_afl/afl-g++ ../../drivers/6_cJSON/driver_1.cpp ../../build/6_cJSON/libcjson.a -o driver_1 -static
        ../../build/1_afl/afl-g++ ../../drivers/6_cJSON/driver_2.cpp ../../build/6_cJSON/libcjson.a -o driver_2 -static
    )
}
build_7_TheAlgorithmsC_drivers() {
    (
        mkdir -p fuzzTargets/7_TheAlgorithmsC
        cd fuzzTargets/7_TheAlgorithmsC
        ../../build/1_afl/afl-g++ ../../drivers/7_TheAlgorithmsC/driver_1.cpp -o ./driver_1 -static
        ../../build/1_afl/afl-g++ ../../drivers/7_TheAlgorithmsC/driver_2.cpp -o ./driver_2 -static
    )
}

build_8_spdlog() {
    (
        mkdir -p fuzzTargets/8_spdlog
        cd fuzzTargets/8_spdlog
        ../../build/1_afl/afl-g++ -I../../projectFiles/8_spdlog/include/ ../../drivers/8_spdlog/driver_1.cpp -o ./driver_1 ../../build/8_spdlog/libspdlog.a -static
        ../../build/1_afl/afl-g++ -I../../projectFiles/8_spdlog/include/ ../../drivers/8_spdlog/driver_2.cpp -o ./driver_2 ../../build/8_spdlog/libspdlog.a -static        
    )
}

build_9_iostream() {
    (
        mkdir -p fuzzTargets/9_iostream
        fuzzTargets/9_iostream
        g++ ../../drivers/9_iostream/driver_1.cpp --static -o ./driver_1
        g++ ../../drivers/9_iostream/driver_2.cpp --static -o ./driver_2
    )
}

build_X_libqalculate() {
    (
        mkdir -p fuzzTargets/X_libqalculate
        cd fuzzTargets/X_libqalculate
        ../../build/1_afl/afl-g++ -I../../projectFiles/X_libqalculate ../../drivers/X_libqalculate/driver_1.cpp -o ./driver_1 ../../build/X_libqalculate/libqalculate/.libs/libqalculate.a -lgmp -lmpfr -lcurl -lxml2 -ldl -pthread -licuuc
        ../../build/1_afl/afl-g++ -I../../projectFiles/X_libqalculate ../../drivers/X_libqalculate/driver_2.cpp -o ./driver_2 ../../build/X_libqalculate/libqalculate/.libs/libqalculate.a -lgmp -lmpfr -lcurl -lxml2 -ldl -pthread -licuuc
    )
}