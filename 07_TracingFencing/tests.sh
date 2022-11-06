#!/bin/bash

tests_runner="./run_test.sh"

errors="ENOENT
ENAMETOOLONG
ELOOP
EACCES
EROFS
ETXTBSY
EFAULT
ENOMEM
EMFILE"

exit_codes="2 2 2 3 3 3 4 4 4"

sys_calls="openat read write close unlink"
max_when="2 1 1 2 1"

OLD_IFS="$IFS"
IFS=$'\n' errors=($errors)
IFS=$' ' exit_codes=($exit_codes)
IFS=$' ' sys_calls=($sys_calls)
IFS=$' ' max_when=($max_when)
IFS="$OLD_IFS"

for i in ${!sys_calls[@]}; do
    sys_call=${sys_calls[$i]}
    echo "### Tests for $sys_call ###"
    for when in $(seq 1 ${max_when[$i]}); do
        if [ "$sys_call" = "write" ] || [ "$sys_call" = "unlink" ] || [ "$when" = "2" ]; then
            file_name="Output"
        else
            file_name="Input"
        fi
        echo "*** $file_name file ***"

        for j in ${!errors[@]}; do
            "$tests_runner" "$sys_call" "${errors[$j]}" -e "${exit_codes[$j]}" -w "$when"
        done
        echo
    done

    printf "*** No errors ***\n"
    for i in ${!errors[@]}; do
        "$tests_runner" "$sys_call" "${errors[$i]}" -w 99
    done
    echo
done


echo "### Tests for LD_PRELOAD ###"
./run_ld_preload_test.sh "qwe"
./run_ld_preload_test.sh "kkkkkkkkk"
./run_ld_preload_test.sh "filename"
./run_ld_preload_test.sh "PROTECT"
./run_ld_preload_test.sh "___PROTECT"
./run_ld_preload_test.sh "PROTECT&&&&&"
./run_ld_preload_test.sh "qooo_PROTECT_asdsd"
