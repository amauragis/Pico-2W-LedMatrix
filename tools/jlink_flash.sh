#!/bin/sh

THIS_DIR=$(dirname "$(realpath "$0")")
(
    cd "$THIS_DIR" || exit
    JLinkExe -Device RP2350_M33_0 -CommandFile ${THIS_DIR}/segger/flash.jlink -NoGui 1 -ExitOnError 1
)
