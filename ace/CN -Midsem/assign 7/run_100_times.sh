#!/bin/bash
count=0
for ((i=0; i<100; i++))
do
if ./t2 5; then
echo "Run $i: No deadlock"
else
echo "Run $i: Deadlock occurred"
((count++))
fi
done
echo "Number of deadlocks encountered:$count"
