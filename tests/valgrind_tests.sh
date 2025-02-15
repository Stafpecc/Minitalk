#!/bin/bash

cd exec || exit

# Run Valgrind to check for memory leaks
echo "Running Valgrind..."
valgrind --leak-check=full --track-origins=yes --verbose ./server &
SERVER_PID=$!
./client $SERVER_PID "Valgrind test message"
kill $SERVER_PID
