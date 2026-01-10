#!/usr/bin/env bash

set -eou pipefail

cmake --preset profile

cmake --build build/profile

perf record -g ./build/profile/app

hotspot perf.data &>/dev/null &
