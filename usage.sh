#!/bin/sh

set -e

cmake -B builddir -DCMAKE_BUILD_TYPE=Release
cmake --build builddir --config Release
