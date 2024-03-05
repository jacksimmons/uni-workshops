#!/bin/bash

# Run the sine program for numbers from -3.0 to 3.0 in steps of 0.4
# Used in ECM3446/ECMM461 workshop 5


# The seq command generates the values to be iterated over
for val in `seq -6.0 0.4 6.0`; do 
    echo "*** Calcuating sin ${val} ***"
# Run the sine program and use grep to extract the line of output 
# which says how many terms have been computed
    ./sine ${val} | grep computed
    echo
done

# End of file
