#!/bin/bash

user_output=$(mktemp)

for testnum in $@; do
    testin=tests/$testnum.in
    testout=tests/$testnum.out
    testgen=tests/$testnum.gen

    echo -n "Running test $testnum"
    [ -f "$testgen" ] && echo -n " ($(cat "$testgen"))"
    echo
    #echo $SOLUTION  "$testin"  "$user_output"
    $SOLUTION < "$testin" > "$user_output"
    code=$?
    if [ $code -ne 0 ]; then
        echo Tested program crashed with return code $code
        exit 1
    fi

    #echo $GRADER "$testout" "$user_output" "$testin"
    grader_output=$($GRADER "$testout" "$user_output" "$testin")
    { read -r grading_result; read -r grading_score; } <<< "$grader_output" || true
    code=$?
    if [ $code -ne 0 ]; then
        echo Grader crashed with return code $code
        [[ -z "$NONSTOP" ]] && exit 2
    fi
    if [ "$grading_result" != "1" ]; then
        echo Grader returned $grading_result
        [[ -z "$NONSTOP" ]] && exit 3
    fi
    if [ ! -z "$grading_score" ]; then
        echo Grader gave score $grading_score
    fi
done
