#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck ./main.cc --enable=all --inconclusive --error-exitcode=1 -I ./matrix_calculator_lib

print_header "RUN clang-tidy"
clang-tidy ./main.cc -- -I matrix_calculator_lib

print_header "RUN cpplint.py"
python3 -m cpplint matrix_calculator_lib/* tests/* main.cc

print_header "SUCCESS"
