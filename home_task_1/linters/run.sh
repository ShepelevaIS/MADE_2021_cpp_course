#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck specialists_db_lib --enable=all --inconclusive --error-exitcode=1 -I ./specialists_db_lib

print_header "RUN clang-tidy"
clang-tidy specialists_db_lib/* -- -I specialists_db_lib
clang-tidy tests/* -- -I tests

print_header "RUN cpplint.py"
python3 ./linters/cpplint/cpplint.py --extensions=c specialists_db_lib/* tests/*

print_header "SUCCESS"