#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck . --enable=all --inconclusive --error-exitcode=1 -I ./home_task_2/matrix_calculator_lib

print_header "RUN clang-tidy"
# clang-tidy ./home_task_2/matrix_calculator_lib/* -- -I home_task_2/matrix_calculator_lib

print_header "RUN cpplint.py"
python3 /home_task_2/linters/cpplint/cpplint.py --extensions=c home_task_2/matrix_calculator_lib/* home_task_2/tests/*

print_header "SUCCESS"