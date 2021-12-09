#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

# print_header "RUN cppcheck sequential"
# cppcheck ./main.cc --enable=all --inconclusive --error-exitcode=1 -I ./countif_sequential_lib

# print_header "RUN cppcheck parallel"
# cppcheck ./main.cc --enable=all --inconclusive --error-exitcode=1 -I ./countif_parallel_lib

# print_header "RUN clang-tidy sequential"
# clang-tidy ./main.cc --  -I ./countif_sequential_lib --std=c++2a

# print_header "RUN clang-tidy parallel"
# clang-tidy ./main.cc --  -I ./countif_parallel_lib -pthread --std=c++2a

print_header "RUN cpplint.py"
python3 -m cpplint countif_lib/* countif_sequential_lib/* countif_parallel_lib/* main.cc

print_header "SUCCESS"
