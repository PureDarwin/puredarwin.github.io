#!/bin/bash
while IFS='' read -r line || [[ -n $line ]]; do
    wget http://www.puredarwin.org/$line
done < "$1"
