#!/usr/bin/env bash

set -eou pipefail

function run_profile()
{
	local binary="./build/profile/App/app"

	cmake --preset profile

	cmake --build build/profile

	perf record -g "$binary"

	hotspot perf.data &>/dev/null &
}

function run_debug()
{
	local binary="./build/App/app"
	local local_host="1234"

	cmake --preset debug
	cmake --build build

	if [[ ${TMUX+x} ]]; then
		tmux split-window -h -p 50 "gdbserver :${local_host} ./${binary}"
		tmux select-pane -t left
		gdb -q --tui -ex "target remote :${local_host}"
	else
		gdb -q --tui "${binary}"
	fi
}

function run()
{
	local binary="./build/App/app"

	cmake --preset debug
	cmake --build build

	exec "$binary"
}

MODE="${1-}"

case "$MODE" in
	profile | p)
		run_profile
		;;
	debug | d)
		run_debug
		;;
	run | r)
		run
		;;
	*)
		run
		;;
esac
