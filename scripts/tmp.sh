#!/bin/bash

list=()

for item in "${list[@]}"; do
	echo " >> Searching for '$item'"
	grep -i "$item" -r ./resources/reanims

	echo "\n"
done

