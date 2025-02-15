#!/bin/bash

# Color variables for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No color

# Function to print OK/KO with colors and track test results
test_result() {
    if [ "$1" -eq 0 ]; then
        echo -e "${GREEN}[OK]${NC} $2"
        results+=("OK")
    else
        echo -e "${RED}[KO]${NC} $2"
        results+=("KO")
    fi
}

# Loading bar function
loading_bar() {
    echo -n "$1"
    for i in {1..30}; do
        sleep 0.01
        echo -n "."
    done
    echo ""
}

# Initialize results array
results=()

cd exec || exit

echo -e "${BLUE}Running basic tests...${NC}"
./server &
SERVER_PID=$!
sleep 1

# Spam test: Send a large number of messages
echo -e "${BLUE}Running spam test...${NC}"
loading_bar "Sending 1000 spam messages"
for i in {1..1000}; do
    ./client "$SERVER_PID" "Spam message $i"
    if [ "$?" -ne 0 ]; then
        test_result 1 "Spam message $i"
        exit 1
    fi
done
test_result 0 "Spam messages sent"

# Basic message tests
loading_bar "Sending normal messages"
./client "$SERVER_PID" "Lorem ipsum dolor sit amet" && test_result $? "Lorem ipsum"
./client "$SERVER_PID" "😊🎉🚀❤️" && test_result $? "Emoji message"
./client "$SERVER_PID" "!@#\$%\^&\*\(\)_\+-=~\`{}[]|:;'<>,.?/" && test_result $? "Special chars message"
./client "$SERVER_PID" "" && test_result $? "Empty message"
./client "$SERVER_PID" "Hello,\nMinitalk!" && test_result $? "Message with newline"
./client "$SERVER_PID" "A" && test_result $? "Single character"
./client "$SERVER_PID" "This is a very long message with special characters like € and ñ." && test_result $? "Long message with special characters"
sleep 1

# Random disconnection test: Kill the server and check if the client can reconnect
echo -e "${BLUE}Running random disconnection test...${NC}"
./client "$SERVER_PID" "Message before kill"
kill -9 "$SERVER_PID"
sleep 2 # Wait for the server to die
./server &
SERVER_PID=$!
sleep 2 # Wait for the server to start
./client "$SERVER_PID" "Message after kill" && test_result $? "Message after reconnect"

# Corrupted message test: Send invalid bytes to the server
echo -e "${BLUE}Running corrupted message test...${NC}"
loading_bar "Sending corrupted message"
./client "$SERVER_PID" "$(echo -ne '\x80\x81\x82')" && test_result $? "Corrupted message"

# Invalid PID test: Send a message to an invalid PID
echo -e "${BLUE}Running invalid PID test...${NC}"
loading_bar "Sending message to invalid PID"
./client 99A9E99T9 "Invalid PID test" && test_result $? "Invalid PID test"

# Invalid message test: Send a message with invalid characters
echo -e "${BLUE}Running invalid message test...${NC}"
loading_bar "Sending invalid message"
./client "$SERVER_PID" "$(echo -ne '\x00\x01\x02')" && test_result $? "Invalid message"

# Function to run a client with an invalid message in the stress test
run_invalid_message_client() {
    ./client "$SERVER_PID" "$(echo -ne '\x00\x01\x02')" &  # Run client in the background
    local pid=$!
    wait $pid
    test_result $? "Invalid message from client"
}

# Stress test: Launch multiple clients to send messages concurrently
echo -e "${BLUE}Running multiple clients test...${NC}"
loading_bar "Launching multiple clients sequentially"

for i in {1..10}; do # Launch 10 clients
    echo "===== Client $i ====="
    ./client "$SERVER_PID" "Message from client $i"
    if [ $? -eq 0 ]; then # Check if the client sent the message successfully
        echo -e "${GREEN}Client $i message sent successfully${NC}"
    else
        echo -e "${RED}Client $i failed to send message${NC}"
    fi
    sleep 0.5
done

test_result 0 "Multiple clients sent sequentially"

# Signal test: Test server behavior with signals like SIGSTOP and SIGCONT
echo -e "${BLUE}Running signal test...${NC}"
loading_bar "Sending signal tests"
kill -STOP "$SERVER_PID"
sleep 2
kill -CONT "$SERVER_PID"
./client "$SERVER_PID" "Message after pause" && test_result $? "Signal test"

# Shutdown the server
kill "$SERVER_PID"

# Final summary
echo -e "${YELLOW}Test Summary:${NC}"
passed=0
failed=0
for result in "${results[@]}"; do
    if [ "$result" == "OK" ]; then
        ((passed++))
    else
        ((failed++))
    fi
done

echo -e "${GREEN}$passed tests passed.${NC}"
echo -e "${RED}$failed tests failed.${NC}"

if [ "$failed" -eq 0 ]; then
    echo -e "${GREEN}All tests passed successfully!${NC}"
else
    echo -e "${RED}Some tests failed.${NC}"
fi
