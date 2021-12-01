#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck ./home_task_2/main.cc --enable=all --inconclusive --error-exitcode=1 -I ./home_task_2/matrix_calculator_lib

print_header "RUN clang-tidy"
clang-tidy ./home_task_2/main.cc -- -I home_task_2/matrix_calculator_lib

print_header "RUN cpplint.py"
cd ./home_task_2/ && python3 linters/cpplint/cpplint.py --extensions=c matrix_calculator_lib/* tests/*

print_header "SUCCESS"