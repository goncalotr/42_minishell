#!/bin/bash

# --- Colors ---
RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"
WHITE="\033[37m"
YELLOW="\033[33m"
BLUE="\033[34m"

# --- Symbols / Emojis ---
CHECKMARK="✅"
CROSSMARK="❌"
GEAR="⚙️"
FOLDER="📁"
SPARKLES="✨"

echo -e "${BLUE}--- Test Start ---${BLUE}"
echo -e "${BLUE}---${RESET}"
echo

echo -e "${YELLOW}--- Basic Setup ---${RESET}"

export EXP_TEST_VAR="World"
export EXP_EMPTY_VAR=""
export EXP_SPACE_VAR="Hello Mars"
echo "Set EXP_TEST_VAR=World"
echo "Set EXP_EMPTY_VAR="
echo "Set EXP_SPACE_VAR='Hello Mars'"
echo ""

echo -e "${YELLOW}--- Testing \$? ---${RESET}"

/bin/true # Set exit status to 0
echo "Exit status should be 0: $?"
/bin/false # Set exit status to 1
echo "Exit status should be 1: $?"
ls /nonexistent_file_for_error > /dev/null 2>&1 # Set non-zero status (likely 1 or 2)
echo "Exit status should be non-zero: $?"
echo "Combined status: $? - testing"
echo ""

echo -e "${YELLOW}--- Testing \$VAR ---${RESET}"

echo "Simple var: $EXP_TEST_VAR"
echo "Existing var: $USER" # Assumes USER is set
echo "Non-existent var: $EXP_NON_EXISTENT" # Should be empty
echo "Empty var: $EXP_EMPTY_VAR" # Should be empty
echo "Combined: Hello_$EXP_TEST_VAR!"
echo "Multiple: $EXP_TEST_VAR $USER"
echo "Space var (no word splitting yet): $EXP_SPACE_VAR"
echo ""

echo -e "${YELLOW}--- Testing \${VAR} ---${RESET}"

echo "Simple var: ${EXP_TEST_VAR}"
echo "Existing var: ${USER}" # Assumes USER is set
echo "Non-existent var: ${EXP_NON_EXISTENT}" # Should be empty
echo "Empty var: ${EXP_EMPTY_VAR}" # Should be empty
echo "Combined: Hello_${EXP_TEST_VAR}!"
echo "Multiple: ${EXP_TEST_VAR} ${USER}"
echo "Space var (no word splitting yet): ${EXP_SPACE_VAR}"
echo "Delimiting: ${EXP_TEST_VAR}suffix"
echo ""

echo -e "${YELLOW}--- Testing Edge Cases & Invalid ---${RESET}"

echo "Literal dollar at end: $"
echo "Literal dollar followed by space: $ hello"
echo "Literal dollar followed by number: $1" # Not handled, should be literal $1
echo "Literal dollar followed by dollar: $$" # Not handled, should be literal $$
echo "Invalid curly syntax (no closing brace): \${EXP_TEST_VAR" # Should treat initial $ literally
echo "Just curly braces: \${}" # Should likely treat initial $ literally
echo "Var name starting with number: $1VAR" # Should treat initial $ literally
echo ""

echo -e "${YELLOW}--- Testing Quoting ---${RESET}"

echo "Single quotes (bash: no expand, current: expands): '$EXP_TEST_VAR'"
echo "Single quotes (bash: no expand, current: expands): 'Status $?'"
echo "Double quotes (bash: expands, current: expands): \"$EXP_TEST_VAR\""
echo "Double quotes (bash: expands, current: expands): \"Status $?\""
echo ""

echo -e "${YELLOW}--- Unsetting Test Vars ---${RESET}"

unset EXP_TEST_VAR
unset EXP_EMPTY_VAR
unset EXP_SPACE_VAR
echo "Test vars unset."

echo
echo -e "${GREEN}---${RESET}"
echo -e "${GREEN}--- End of Tests ---${GREEN}"
