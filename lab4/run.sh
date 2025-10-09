#!/usr/bin/env bash


for i in q*; do
    echo RUNNING "$i" 
    g++ "$i" -o main
    ./main
    rm main
    echo;echo;
done
