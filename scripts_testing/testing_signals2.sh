      
# ==============================================================================
#      MINISHELL SIGNAL HANDLING TEST SUITE (42 Subject Compliant)
# ==============================================================================
# INSTRUCTIONS:
# 1. Run your minishell: ./minishell
# 2. Copy and paste each command block.
# 3. Perform the action described in the INSTRUCTIONS.
# 4. Compare your shell's output to the # EXPECTED: comment.
# ==============================================================================

echo "--- SECTION 1: INTERACTIVE PROMPT SIGNALS ---"
echo ""
echo "Test 1.1: Ctrl+C at an empty prompt"
# INSTRUCTIONS: Press Ctrl+C now.
# EXPECTED: A new, clean prompt appears on the next line. The shell does not exit.

echo "Test 1.2: Check exit status after Ctrl+C at prompt"
echo $?
# EXPECTED: 130

echo ""
echo "Test 1.3: Ctrl+\ (SIGQUIT) at prompt"
# INSTRUCTIONS: Press Ctrl+\ now.
# EXPECTED: CORRECT (42 Subject): Absolutely nothing happens. The prompt is unaffected.
#           (This is different from bash, which does nothing but also doesn't show '^').

# --- SECTION 2: RUNNING COMMAND SIGNALS ---

echo ""
echo "--- SECTION 2: RUNNING COMMAND SIGNALS ---"
echo "Test 2.1: Interrupting a running command with Ctrl+C"
echo "INSTRUCTIONS: Command 'sleep 5' will run. Press Ctrl+C while it is running."
sleep 5
# EXPECTED: A newline `\n` is printed, and a new prompt appears immediately.

echo "Test 2.2: Check exit status after interrupting with Ctrl+C"
echo $?
# EXPECTED: 130

echo ""
echo "Test 2.3: Quitting a running command with Ctrl+\ "
echo "INSTRUCTIONS: Command 'sleep 5' will run. Press Ctrl+\ while it is running."
sleep 5
# EXPECTED: The shell prints "Quit (core dumped)" and then a new prompt.
#           Your shell (the parent) MUST NOT exit.

echo "Test 2.4: Check exit status after quitting with Ctrl+\ "
echo $?
# EXPECTED: 131 (128 + SIGQUIT)

# --- SECTION 3: HEREDOC AND EOF SIGNALS ---

echo ""
echo "--- SECTION 3: HEREDOC AND EOF SIGNALS ---"
echo "Test 3.1: Interrupting a heredoc with Ctrl+C"
echo "INSTRUCTIONS: The shell will wait for heredoc input ('>' prompt). Press Ctrl+C."
cat << EOF
# EXPECTED: The heredoc input is cancelled. You get a new prompt immediately.
#           The `cat` command does not run.

echo "Test 3.2: Check exit status after canceling heredoc"
echo $?
# EXPECTED: 130

echo ""
echo "Test 3.3: Ctrl+D on an empty line (EOF)"
echo "INSTRUCTIONS: Make sure the line is empty, then press Ctrl+D."
# EXPECTED: The shell prints "exit" and terminates gracefully.

# --- End of tests ---

    