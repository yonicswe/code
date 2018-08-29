#!/bin/bash

fileName="$1"

newFileName=$(echo "$fileName" | sed 's/\ /_/g')
mv -v "$fileName" $newFileName

