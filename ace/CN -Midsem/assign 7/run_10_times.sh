#!/bin/bash
count=0
for ((i=0; i<10; i++))
do
if ./t3 5; then
echo "Run $i: No deadlock"
else
echo "Run $i: Deadlock occurred"
((count++))
fi
done
echo "Number of deadlocks encountered: $count"
