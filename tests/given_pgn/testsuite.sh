#!/bin/sh

for file in *.pgn; do
    ../../build/chessengine --pgn "$file" -l ../libbasic-output.so > "out.txt"
    res=$(diff "out.txt" "${file%.pgn}.out")
    if [ -z "$res" ]; then
        echo "[PASS] $file"
    else
        echo "[FAIL] $file"
        echo "diff: "
        echo "$res"
    fi
done

rm -f out.txt
