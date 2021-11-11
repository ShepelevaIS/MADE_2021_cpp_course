#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck . --enable=all --inconclusive --error-exitcode=1 -I ./matrix_calculator_lib

print_header "RUN clang-tidy"
# clang-tidy ./matrix_calculator_lib/* -- -I matrix_calculator_lib

print_header "RUN cpplint.py"
python3 ./linters/cpplint/cpplint.py --extensions=c matrix_calculator_lib/* tests/*

print_header "SUCCESS"