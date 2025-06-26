      
# ==============================================================================
#      MINISHELL QUOTE & EXPANSION TEST SUITE (Plain Text Version)
# ==============================================================================

# --- Test Suite Setup ---
echo ""
echo "================================================="
echo "      MINISHELL QUOTE & EXPANSION TEST SUITE     "
echo "================================================="
export TEST_USER=$USER
echo "--- Starting tests with TEST_USER=$USER ---"


# === SECTION 1: SINGLE QUOTES ('') ===
echo ""
echo "=== SECTION 1: SINGLE QUOTES ('') ==="
echo "--- Single quotes must treat every character literally. ---"

echo ""
echo "Test 1.1: Basic literal string"
echo 'Hello World'
echo "EXPECTED: Hello World"

echo ""
echo "Test 1.2: No variable expansion"
echo 'Your user is $TEST_USER'
echo "EXPECTED: Your user is \$TEST_USER"

echo ""
echo "Test 1.3: No special character interpretation"
echo 'Special characters: | > < * $ ` \ '
echo "EXPECTED: Special characters: | > < * \$ \` \\ "

echo ""
echo "Test 1.4: Nested double quotes are literals"
echo 'A string with "double quotes" inside.'
echo "EXPECTED: A string with \"double quotes\" inside."


# === SECTION 2: DOUBLE QUOTES ("") ===
echo ""
echo "=== SECTION 2: DOUBLE QUOTES (\"\") ==="
echo "--- Double quotes must expand variables but protect literals. ---"

echo ""
echo "Test 2.1: Basic literal string"
echo "Hello World"
echo "EXPECTED: Hello World"

echo ""
echo "Test 2.2: Variable expansion MUST happen"
echo "Your user is $TEST_USER"
echo "EXPECTED: Your user is $USER"

echo ""
echo "Test 2.3: Most special characters are literal"
echo "Special characters: | > < *"
echo "EXPECTED: Special characters: | > < *"

echo ""
echo "Test 2.4: Nested single quotes are literals"
echo "A string with 'single quotes' inside."
echo "EXPECTED: A string with 'single quotes' inside."


# === SECTION 3: WORD SPLITTING AND SPACES ===
echo ""
echo "=== SECTION 3: WORD SPLITTING & SPACES ==="
echo "--- Critical test for unquoted vs. quoted expansion. ---"

echo ""
echo "Test 3.1: Create a variable with spaces"
export SPACEY_VAR="  leading and    multiple   trailing spaces  "
echo "Variable SPACEY_VAR has been set."

echo ""
echo "Test 3.2: Unquoted expansion -> word splitting occurs"
echo $SPACEY_VAR
echo "EXPECTED: leading and multiple trailing spaces"

echo ""
echo "Test 3.3: Quoted expansion -> word splitting is suppressed"
echo "$SPACEY_VAR"
echo "EXPECTED:   leading and    multiple   trailing spaces  "


# === SECTION 4: MIXED AND ADJACENT QUOTES ===
echo ""
echo "=== SECTION 4: MIXED & ADJACENT QUOTES ==="
echo "--- Testing concatenation of quoted/unquoted strings. ---"

echo ""
echo "Test 4.1: Simple concatenation"
echo 'Hello'World
echo "EXPECTED: HelloWorld"

echo ""
echo "Test 4.2: Mixed quote concatenation"
echo "Hello "'World'
echo "EXPECTED: Hello World"

echo ""
echo "Test 4.3: Concatenation with expansion (part 1)"
echo "User: "'$TEST_USER'
echo "EXPECTED: User: \$TEST_USER"

echo ""
echo "Test 4.4: Concatenation with expansion (part 2)"
echo 'User: '"$TEST_USER"
echo "EXPECTED: User: $USER"


# === SECTION 5: EMPTY STRINGS AND ARGUMENTS ===
echo ""
echo "=== SECTION 5: EMPTY STRINGS & ARGUMENTS ==="
echo "--- Testing edge cases with empty values. ---"

echo ""
echo "Test 5.1: Empty double quotes"
echo ""
echo "EXPECTED: "

echo ""
echo "Test 5.2: Empty single quotes"
echo ''
echo "EXPECTED: "

echo ""
echo "Test 5.3: Adjacent empty quotes forming one argument"
echo hello""world
echo "EXPECTED: helloworld"


# === SECTION 6: SYNTAX ERRORS ===
echo ""
echo "=== SECTION 6: SYNTAX ERRORS ==="
echo "--- Shell must not crash and should report an error. ---"

echo ""
echo "Test 6.1: Unclosed single quote"
echo 'hello world
echo "EXPECTED: minishell: Syntax error: unclosed quotes (or similar)"

echo ""
echo "Test 6.2: Unclosed double quote"
echo "hello world
echo "EXPECTED: minishell: Syntax error: unclosed quotes (or similar)"


# --- Footer ---
echo ""
echo "--- Tests complete ---"

    