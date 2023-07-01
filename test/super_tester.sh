#!bin/bash

input=
expected_output=

## Syntax error test

input1=|
expected_output1=

input2=cat |
expected_output=

input3= ||
expected_output=

input4= cat || cat
expected_output=

input5= || cat
expected_output=



#!/bin/bash

# Define test cases
declare -a inputs=("input1" "input data 2" "input data 3")
declare -a expected_outputs=("expected output 1" "expected output 2" "expected output 3")

# Iterate over test cases
for ((i=0; i<${#inputs[@]}; i++)); do
    input=${inputs[$i]}
    expected_output=${expected_outputs[$i]}

    # Run the test case
    output=$(./your_program "$input" 2>&1)

    # Compare the output
    if [ "$output" = "$expected_output" ]; then
        echo "Test case $((i+1)): Passed"
    else
        echo "Test case $((i+1)): Failed"
        echo "Expected output: $expected_output"
        echo "Actual output: $output"
    fi
done
