#!/bin/bash

if [ $# -ne 1 ]; then
    echo "There should be 1 positional argument!"
    exit 1
fi

in_file="$1"
out_file="out.file"
in_check_file="check-$in_file"

content="1 + 1 = 2\n2 * 2 = 4\n123123213\n\n\n\n\n\t\t\t\t123 12 3 123 213 2  32 3 2 323\n\n1 3 12 32 32     123 2     \n 1      12 3 \n\n      df    \n     \n\n\n"

printf "$content" > "$in_file"
cp "$in_file" "$in_check_file"

LD_PRELOAD=./remove.so ./move "$in_file" "$out_file"

test_name="$in_file"
printf "%-20s: " "$test_name"

verdict="OK"
if ! ( cmp -s "$in_check_file" "$out_file" ); then
    verdict="WA"
elif [[ "$in_file" == *"PROTECT"* ]]; then
    if ! ( cmp -s "$in_check_file" "$in_file" ); then
        verdict="WA"
    fi
elif [ -f "$in_file" ]; then
    verdict="WA"
fi

echo "$verdict"

rm -f "$in_file" "$out_file" "$in_check_file"
