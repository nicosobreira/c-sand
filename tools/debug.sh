#!/usr/bin/env bash

set -eou pipefail

TARGET="$1"
LOCAL_HOST="1234"

cmake --preset debug
cmake --build build

if [[ ${TMUX+x} ]]; then
	tmux split-window -h -p 50 "gdbserver :${LOCAL_HOST} ./${TARGET}"
	tmux select-pane -t left
	gdb -q --tui -ex "target remote :${LOCAL_HOST}"
else
	gdb -q --tui "${TARGET}"
fi
