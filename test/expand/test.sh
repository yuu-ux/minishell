#!/bin/bash

test_cases_program=(
    '"$LANG"'
    '"$LANGUAGE"'
    "\$LANG"
    "\$LANGUAGE"
    "'\${USER}'"
    '"Hello $USER"'
    "'\$HOME'"
    '"$HOME"'
    "\$UNDEFINED"
    '"$HOME $USER"'
    '"$PATH $USER"'
)

test_cases_shell=(
    "$LANG"
    "$LANGUAGE"
    $LANG
    $LANGUAGE
    '${USER}'
    "Hello $USER"
    '$HOME'
    "$HOME"
    "$UNDEFINED"
    "$HOME $USER"
    "$PATH $USER"
)

i=1
RED="\033[31m"
GREEN="\033[32m"
RESET="\033[0m"
for index in "${!test_cases_program[@]}"; do
	p_output="`./expand_test "${test_cases_program[$index]}"`"
	s_output="${test_cases_shell[$index]}"
	if [ "${p_output}" = "${s_output}" ]; then
		echo -e "${GREEN}OK${RESET}"
	else
		echo -e "${RED}NG${RESET}"
	fi
	echo "test_case: ${test_cases_program[$index]}"
	echo "test${i} (program): $p_output"
	echo "test${i} (shell): $s_output"
	echo
    ((i++))
done

