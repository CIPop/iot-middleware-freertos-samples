#! /bin/bash

# Copyright (c) Microsoft. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

set -o errexit # Exit if command failed.
set -o nounset # Exit if variable not set.
set -o pipefail # Exit if pipe failed.

echo -e "::group::FreeRTOS Source"

if [ ! -d "libs/FreeRTOS" ]; then
    git clone https://github.com/FreeRTOS/FreeRTOS.git libs/FreeRTOS
    pushd libs/FreeRTOS
    git checkout -b c8fa483b68c6c1149c2a7a8bc1e901b38860ec9b
    git submodule sync
    git submodule update --init --recursive --depth=1
    popd
fi
TEST_FREERTOS_SRC=`pwd`/libs/FreeRTOS

function binary_exists()
{
    local search_dir=$1
    local filename=$2

    if [ $(find "$search_dir" -name "$filename") ]; then 
      echo "$filename is found in $search_dir"
    else
      echo "$filename not found"
      exit 1
    fi
}

function build() {
    local vendor=$1
    local board=$2
    local outdir=$3

    cmake -G Ninja -DBOARD=$board -DVENDOR=$vendor -B$outdir -DFREERTOS_PATH=$TEST_FREERTOS_SRC .
    cmake --build $outdir
}

echo -e "::group::Building sample for linux port"
build "PC" "linux" "build_pc_linux"
binary_exists "build_pc_linux" "iot-middleware-sample.elf"
