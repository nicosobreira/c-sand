#!/usr/bin/env bash

set -eou pipefail

BINARY="./build/app"

cmake --preset debug

cmake --build build

if [[ ${1:-} =~ "debug" ]]; then
	./tools/debug.sh "$BINARY"
	exit 0
fi

exec "$BINARY"
