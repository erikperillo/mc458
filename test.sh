#!/bin/sh

dir=$1

[ -z "$dir" ] && { echo "invalid args"; exit 1; }

program=$dir

cd $dir

make

for test_case in tests/*.in; do
	echo "--- in $test_case.in ---"
	echo "program output:"
	./$(basename $program) < $test_case
	echo "expected output:"
	cat $(echo $test_case | rev | cut -f1 -d. --complement | rev).res
	echo
done
