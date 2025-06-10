#!/bin/bash

# A simple script to test signal handling of your minishell executable.
# It checks how minishell and its children react to SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\).

# --- Colors for Output ---
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RESET='\033[0m'

# --- Minishell Executable ---
MINISHELL_EXEC="./minishell"

# --- Helper Function ---
print_test_result() {
	local test_name="$1"
	local exit_code="$2"
	local expected_code="$3"

	if [ "$exit_code" -eq "$expected_code" ]; then
		echo -e "${GREEN}PASS:${RESET} $test_name. Minishell exited with status $exit_code."
	else
		echo -e "${RED}FAIL:${RESET} $test_name. Expected exit status $expected_code, but got $exit_code."
	fi
}

# --- Pre-test Check ---
if [ ! -x "$MINISHELL_EXEC" ]; then
	echo -e "${RED}Error: Minishell executable '$MINISHELL_EXEC' not found or not executable.${RESET}"
	echo -e "Please compile your project first."
	exit 1
fi

echo -e "${YELLOW}--- Starting Signal Handling Tests ---${RESET}"

# --- Test 1: SIGINT (Ctrl+C) during a child process ---

echo -e "\n${YELLOW}[TEST 1] Sending SIGINT (like Ctrl+C) to a running command...${RESET}"
# We run minishell in the background with a long-running command.
# The `-c` flag is standard for shells to execute a command string.
# If your shell doesn't support -c, you can use: echo "sleep 10" | ./minishell &
./minishell -c "sleep 10" &
MINISHELL_PID=$!

# Give it a moment to start the child `sleep` process
sleep 0.2

# Send SIGINT to the entire process group started by the shell.
# The "--" and "-" before the PID are crucial for this.
if ps -p $MINISHELL_PID > /dev/null; then
	kill -SIGINT -- -$MINISHELL_PID
else
	echo -e "${RED}FAIL:${RESET} Minishell exited prematurely."
fi

wait $MINISHELL_PID
STATUS=$?
print_test_result "SIGINT on child" $STATUS 130


# --- Test 2: SIGQUIT (Ctrl+\) during a child process ---

echo -e "\n${YELLOW}[TEST 2] Sending SIGQUIT (like Ctrl+\) to a running command...${RESET}"
./minishell -c "sleep 10" &
MINISHELL_PID=$!
sleep 0.2

if ps -p $MINISHELL_PID > /dev/null; then
	# Sending SIGQUIT to the process group. Expect "Quit (core dumped)" message.
	echo "Output from minishell:"
	kill -SIGQUIT -- -$MINISHELL_PID
else
	echo -e "${RED}FAIL:${RESET} Minishell exited prematurely."
fi

wait $MINISHELL_PID
STATUS=$?
print_test_result "SIGQUIT on child" $STATUS 131


# --- Test 3: SIGQUIT (Ctrl+\) at interactive prompt (should be ignored) ---

echo -e "\n${YELLOW}[TEST 3] Sending SIGQUIT to an idle interactive shell (should be ignored)...${RESET}"
# This test is tricky but powerful. We check if the shell is still alive after the signal.
(sleep 1 && kill -SIGQUIT $$) | ./minishell > /dev/null 2>&1 &
MINISHELL_PID=$!
sleep 0.5 # Give it time to receive the signal

# Check if the process is still running. kill -0 returns true if it exists.
if kill -0 $MINISHELL_PID > /dev/null 2>&1; then
	echo -e "${GREEN}PASS:${RESET} SIGQUIT on interactive prompt. Minishell correctly ignored the signal and is still running."
	# Clean up the running process
	kill -KILL $MINISHELL_PID
else
	echo -e "${RED}FAIL:${RESET} SIGQUIT on interactive prompt. Minishell exited when it should have ignored the signal."
fi
# Wait to clean up the process entry
wait $MINISHELL_PID > /dev/null 2>&1

echo -e "\n${YELLOW}--- Tests Complete ---${RESET}"
