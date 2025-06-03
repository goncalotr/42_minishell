#!/bin/bash

# use with:
# bash ./../docs_testing/loop_script.sh

# Duration: 60 seconds (1 minute)
# Interval: 10 seconds
duration=60
interval=10
elapsed=0

echo "Starting 1-minute test loop..."

while [ $elapsed -lt $duration ]; do
    echo "[$(date +%T)] Echo message: $elapsed seconds elapsed."
    sleep $interval
    elapsed=$((elapsed + interval))
done

echo "Test loop completed."
