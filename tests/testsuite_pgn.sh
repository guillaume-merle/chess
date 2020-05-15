#!/bin/sh

print ()
{
    tput setaf "$2"
    echo "$1"
    tput sgr0
}

passed=0
failed=0

for file in given_pgn/*.pgn; do
    ../build/chessengine --pgn "$file" -l ./libbasic-output.so > "out.txt"
    res=$(diff "out.txt" "${file%.pgn}.out")
    if [ -z "$res" ]; then
        print "[PASS] $file" 2
        passed=$((passed + 1))
    else
        print "[FAIL] $file" 5
        echo "diff: "
        echo "$res"
        failed=$((failed + 1))
    fi
done

echo

print "Failed: $failed" 6
print "Total : $((failed + passed))" 6

rm -f out.txt

exit $failed
