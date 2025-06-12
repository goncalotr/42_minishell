#!/bin/bash

#==============================================================================#
# MINISHELL 'ECHO' BUILT-IN TESTER SCRIPT                                      #
#==============================================================================#

###--- ANSI Color Codes ---###
RESET="\033[0m"
# Regular Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
CYAN="\033[0;36m"
# Bold/Bright Colors
B_YELLOW="\033[1;33m"
B_GREEN="\033[1;32m"
B_RED="\033[1;31m"

# --- Setup ---
export TEST_VAR="<is working>"
echo -e "${B_YELLOW}--> Test variable set.${RESET}"

# --- Basic Tests ---
echo ""
echo -e "${B_YELLOW}--- BASIC TESTS ---${RESET}"
echo -e "${CYAN}--> Test 1: Simple string${RESET}"
echo hello world
echo -e "${CYAN}--> Test 2: Multiple spaces preserved by quotes${RESET}"
echo "hello   world"
echo -e "${CYAN}--> Test 3: Just echo (should print a newline)${RESET}"
echo
echo -e "${CYAN}--> Test 4: Empty string (should print a newline)${RESET}"
echo ""

# --- -n Flag Tests ---
echo ""
echo -e "${B_YELLOW}--- -n FLAG TESTS ---${RESET}"
echo -e "${CYAN}--> Test 5: Simple -n flag (no newline)${RESET}"
echo -n hello world
echo -e "${GREEN} (<- if you see this on the same line, it worked)${RESET}"
echo -e "${CYAN}--> Test 6: Multiple -n flags${RESET}"
echo -n -n -n hello world
echo -e "${GREEN} (<- same line?)${RESET}"
echo -e "${CYAN}--> Test 7: Combined flags -nnnn${RESET}"
echo -nnnnn hello world
echo -e "${GREEN} (<- same line?)${RESET}"
echo -e "${CYAN}--> Test 8: -n not at start${RESET}"
echo hello -n world
echo -e "${CYAN}--> Test 9: Just -n${RESET}"
echo -n
echo -e "${GREEN} (<- nothing should be between this and the prompt)${RESET}"

# --- Quote and Variable Tests ---
echo ""
echo -e "${B_YELLOW}--- QUOTE AND VARIABLE TESTS ---${RESET}"
echo -e "${CYAN}--> Test 10: Simple variable expansion${RESET}"
echo The test variable $TEST_VAR
echo -e "${CYAN}--> Test 11: No expansion in single quotes${RESET}"
echo 'The test variable $TEST_VAR'
echo -e "${CYAN}--> Test 12: Expansion in double quotes${RESET}"
echo "The test variable $TEST_VAR"
echo -e "${CYAN}--> Test 13: Non-existent variable${RESET}"
echo "Value is: $NON_EXISTENT_VAR"
echo -e "${CYAN}--> Test 14: Double quotes inside single${RESET}"
echo 'hello "quotes" world'
echo -e "${CYAN}--> Test 15: Single quotes inside double${RESET}"
echo "hello 'quotes' world"

# --- Special Variable Tests ---
echo ""
echo -e "${B_YELLOW}--- SPECIAL VARIABLE TESTS ---${RESET}"
echo -e "${CYAN}--> Test 16: Exit status of last command (success)${RESET}"
/bin/true
echo $?
echo -e "${CYAN}--> Test 17: Exit status of last command (failure)${RESET}"
/bin/false
echo $?
echo -e "${CYAN}--> Test 18: Process ID (\$\$)${RESET}"
echo -e "${B_RED}NOTE: The next line WILL be different in minishell and bash. It should be a number.${RESET}"
echo $$

echo ""
echo -e "${B_GREEN}--- TESTS COMPLETE ---${RESET}"
