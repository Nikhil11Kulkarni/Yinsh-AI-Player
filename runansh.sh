#!/bin/bash

## This is to run the first program WModel.java

if [ -e "WModel.class" ]; then
    java WModel $1
else
    echo "First run build.sh to compile the code"
fi