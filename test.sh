#!/bin/bash

# Simple test of the command interpreter

in="abbabaq"
out="0,3,5;"

[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "PASSED" || echo "FAILED"

in2="abbbaccaabbbbac"
out2="7,8;"

[[ $(./cmd_int <<< "$in2") == "$out2"* ]] && echo "PASSED" || echo "FAILED"

in3="abccbaabcq"
out3="5;"

[[ $(./cmd_int <<< "$in3") == "$out3"* ]] && echo "PASSED" || echo "FAILED"

in4="aabbaaaaaabcbbbbbababbcbaaabbbaaa"
out4="0,1,4,5,6,7,8,17,24,25,26,30,31,32;"

[[ $(./cmd_int <<< "$in4") == "$out4"* ]] && echo "PASSED" || echo "FAILED"
