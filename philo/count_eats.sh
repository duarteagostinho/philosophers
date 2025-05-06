#!/bin/bash

OUTPUT_FILE="eating_counts.txt"

./philo $1 $2 $3 $4 $5 | grep "is eating"| awk '{counts[$2]++} END {for (id in counts) print "Philosopher", id, "ate", counts[id], "times"}' | sort -n -k2
