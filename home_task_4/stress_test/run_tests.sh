#!/usr/bin/env bash

file1=sequential.txt
file2=parallel.txt
output=stress_test_output

mkdir $output

for i in {1..100}
do
  printf 'Test %d: ' "$i"
  ./build/generate_test/generate_test 5000 $i > $output/input.txt
  ./build/countif_sequential < $output/input.txt > $output/$file1 2>/dev/null
  ./build/countif_parallel < $output/input.txt > $output/$file2 2>/dev/null
  if cmp -s $output/"$file1" $output/"$file2"; then
      printf 'The file "%s" is the same as "%s"\n' "$file1" "$file2"
  else
      printf 'The file "%s" is different from "%s"\n' "$file1" "$file2"
      exit 1
  fi
done
