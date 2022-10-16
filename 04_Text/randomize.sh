#!/bin/bash

delay="0s"
if [ -n ${1+x} ]
then
    delay="$1""s"
fi

idxs=()
lines=()

r=0

OLDIFS=$IFS
IFS="\n"
while read -r line || [ -n "$line" ]
do
    IFS=$OLDIFS
    length=$((${#line} - 1))
    lines+=("$line")
    for c in $(seq 0 $length ); do
        idxs+=("$r,$c")
    done

    r=$(($r + 1))
    IFS="\n"
done
IFS=$OLDIFS

idxs=( $(shuf -e "${idxs[@]}") )

IFS=','
tput clear
for idx in "${idxs[@]}"
do
    set -- $idx

    tput cup $1 $2
    ch="${lines[$1]}"
    ch="${ch:$2:1}"
    echo $ch

    sleep $delay
done

tput cup $(($r + 1)) 0

IFS=$OLDIFS
