#!/bin/bash

if "$1"!="" then
	mkdir "$0"
	cd "$0"
	echo "//Auto-generated template file">"$0".c
else
	echo "Missing program name! Try again with correct arguments."
fi
