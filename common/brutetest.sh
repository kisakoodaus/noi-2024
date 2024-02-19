#!/bin/bash

NUM=${NUM:-1}
count=1
while true; do
    testgen=tests/brute.gen
    testin=tests/brute.in
    testout=tests/brute.out.a
    user_output=tests/brute.out.b

    params="${FMT/\%/$NUM}"
    echo "$params" > "$testgen"

    ./generator.exe $params > "$testin"
    code=$?
    if [ $code -ne 0 ]; then
        echo ./generator.exe crashed with return code $code
        echo Generator parameters \(saved to $testgen\): $params
        exit 1
    fi
    ./solver.exe $params < "$testin" > "$testout"
    code=$?
    if [ $code -ne 0 ]; then
        echo ./solver.exe crashed with return code $code
        echo Input file $testin
        exit 1
    fi
    $SOLUTION < "$testin" > "$user_output"
    code=$?
    if [ $code -ne 0 ]; then
        echo Tested program crashed with return code $code
        echo Input file $testin
        exit 1
    fi
    grader_output=$($GRADER "$testout" "$user_output" "$testin")
    code=$?
    { read -r grading_result; } <<< "$grader_output" || true
    if [ $code -ne 0 ]; then
        echo Grader crashed with return code $code
        echo Input file $testin, correct output $testout, program output $user_output
        echo Generator parameters \(saved to $testgen\): $params
        exit 2
    fi
    if [ "$grading_result" != "1" ]; then
        echo Grader returned $grading_result
        echo Input file $testin, correct output $testout, program output $user_output
        echo Generator parameters \(saved to $testgen\): $params
        exit 3
    fi

    [ $count -le 10 ] || [ $((count%100)) -eq 0 ] && echo "$count tests run"
    ((NUM++))
    ((count++))
done
