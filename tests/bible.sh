#!/bin/bash

cd exec || exit
mkdir -p ../tests/logs
LOG_FILE="../tests/logs/server.log"

./server &> "$LOG_FILE" &  
SERVER_PID=$!  

MESSAGE=$(cat "../tests/bible.txt")

MAX_SIZE=500  
TOTAL_LENGTH=${#MESSAGE}  
SENT_LENGTH=0  

for (( i=0; i<${#MESSAGE}; i+=MAX_SIZE )); do # Loop through the message in chunks of MAX_SIZE
    PART="${MESSAGE:$i:$MAX_SIZE}"
    SENT_LENGTH=$((SENT_LENGTH + ${#PART}))

    PROGRESS=$((i / MAX_SIZE + 1))
    echo "Sending part $PROGRESS/8703... Sent: $SENT_LENGTH/$TOTAL_LENGTH chars"

    ./client $SERVER_PID "$PART"  
done

echo "=== Server log content ==="
cat "$LOG_FILE"  

sleep 1  
kill $SERVER_PID  
