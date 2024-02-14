#!/bin/sh

mkdir -p ./links
cd links

for file in $(find ../../test -maxdepth 1 -type f); do
        ln -s $file $(basename $file).link
done
