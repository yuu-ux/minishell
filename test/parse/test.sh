#!/bin/bash

test_case=(
    'ls -la | grep -r hoge'
    'echo $PATH'
    'ls | ls | ls | ls'
)

output=(
'''kind:0
argv:ls
argv:-la
in:-1
out:-1
---------------------------------
kind:1
argv:(nil)
in:-1
out:-1
---------------------------------
kind:0
argv:grep
argv:-r
argv:hoge
in:-1
out:-1
---------------------------------'''
'''kind:0
argv:echo
argv:/fzf-zsh-plugin/bin:/opt/X11/bin/:/Users/ebarayuuga/perl5/bin:/root/.asdf/shims:/root/.asdf/bin:/opt/X11/bin/:/root/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/Users/ebarayuuga/.local/bin:/Users/ebarayuuga/.local/bin
in:-1
out:-1
---------------------------------'''
'''kind:0
argv:ls
in:-1
out:-1
---------------------------------
kind:1
argv:(nil)
in:-1
out:-1
---------------------------------
kind:0
argv:ls
in:-1
out:-1
---------------------------------
kind:1
argv:(nil)
in:-1
out:-1
---------------------------------
kind:0
argv:ls
in:-1
out:-1
---------------------------------
kind:1
argv:(nil)
in:-1
out:-1
---------------------------------
kind:0
argv:ls
in:-1
out:-1
---------------------------------'''
)


RED="\033[31m"
GREEN="\033[32m"
RESET="\033[0m"
for i in ${!test_case[@]};
do
    command_output=$(./parse_test "${test_case[$i]}")
    echo "test_case: ${test_case[$i]}"
    if [ "${command_output}" = "${output[$i]}" ]; then
        echo -e ${GREEN} OK ${RESET}
    else
        echo -e ${RED} NG ${RESET}
    fi
done
