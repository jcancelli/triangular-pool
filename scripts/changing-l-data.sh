#! /bin/bash

# This script generates CSV data that represents the change of final y and final theta
# changing only the input value of L

# Analysis parameters
START_L=1
END_L=30
STEP_L=1

# Simulation parameters
ITERATIONS=1000
MEAN_Y=0
STD_DEV_Y=0.15
MEAN_THETA=0
STD_DEV_THETA=10

# First simulation outside of for loop so csv headers can be outputed
./build/src/triangular_pool \
		--output-csv \
		--csv-headers \
		--n $ITERATIONS \
		--mean-y $MEAN_Y \
		--std-dev-y $STD_DEV_Y \
		--mean-theta $MEAN_THETA \
		--std-dev-theta $STD_DEV_THETA \
		--l $START_L

for ((L=$START_L+$STEP_L; L<=$END_L; L+=$STEP_L))
do
	./build/src/triangular_pool \
		--output-csv \
		--n $ITERATIONS \
		--mean-y $MEAN_Y \
		--std-dev-y $STD_DEV_Y \
		--mean-theta $MEAN_THETA \
		--std-dev-theta $STD_DEV_THETA \
		--l $L
done