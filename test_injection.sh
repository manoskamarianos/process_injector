#!/bin/bash


target=$1
file=$2
pid=$(pgrep $target)
address=$(cat /proc/$pid/maps | head -2 | tail -1 | cut -d- -f1)

echo "Injecting $pid at $address..."
sudo ./process_injector $pid 0x$address $file
