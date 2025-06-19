# Unset Testing

## Setup

```bash
# Create a standard exported variable
export EXPORTED_VAR="I will be unset"

# Create a variable that is only local (not exported)
LOCAL_VAR="I am a local variable"

# Create multiple variables for a multi-argument test
export VAR_A="aaa"
export VAR_B="bbb"

echo "Setup complete. Environment is ready."
```

Initial check
```bash
env | grep "EXPORTED_VAR" # Should show the variable
echo $LOCAL_VAR           # Should show "I am a local variable"
```

## Basic Testing

### Test 1

```bash
unset EXPORTED_VAR


# Verification (The variable should be gone from everywhere)
# 1. Check `env`
env | grep "EXPORTED_VAR"  # Expected: No output
# 2. Check `export`
export | grep "EXPORTED_VAR" # Expected: No output
# 3. Check expansion
echo "Value is: $EXPORTED_VAR" # Expected: Value is:
```

### Test 2

```bash
unset LOCAL_VAR

# Verification
echo "Value is: $LOCAL_VAR" # Expected: Value is:
```

### Test 3

```bash
unset VAR_A VAR_B

# Verification
env | grep "VAR_A" # Expected: No output
env | grep "VAR_B" # Expected: No output
```

## Edge Cases

### Test 1

```bash
unset THIS_VARIABLE_DOES_NOT_EXIST

# Verification
echo $?
```

### Test 2

```bash
unset

# Verification
echo $?
```

## Error Handling

### Test 1

```bash
unset "bad-name"

# Verification
echo $?
```

### Test 2

```bash
# Action
unset 1BADVAR

# Verification
echo $?
```

### Test 3

Mix of valid and invalid identifiers

```bash
# Setup
export WILL_BE_UNSET="gone"
export "bad-name" # This might fail on setup, that's okay
export WONT_BE_UNSET="still here"

# Action
unset WILL_BE_UNSET "bad-name" WONT_BE_UNSET

# Verification
# 1. Check that the first valid var was unset
env | grep "WILL_BE_UNSET" # Expected: No output
# 2. Check that the var after the error was NOT unset
env | grep "WONT_BE_UNSET"
# 3. Check the exit status
echo $?
```

No cleanup needed.

```bash
    ~        0.91   94%   7.66G   0B   x86_64   at 20:02:19  
❯ bash
goteixei@c2r6s3:~$ unset GOOD_VAR WONT_BE_SET
goteixei@c2r6s3:~$ export GOOD_VAR=1 "BAD-VAR"=2 WONT_BE_SET=3
bash: export: `BAD-VAR=2': not a valid identifier
goteixei@c2r6s3:~$ env | grep GOOD_VAR
GOOD_VAR=1
goteixei@c2r6s3:~$ env | grep WONT_BE_SET
WONT_BE_SET=3
goteixei@c2r6s3:~$ echo $?
0
goteixei@c2r6s3:~$ 
```

```bash
    ~/42/p/42_minishell/minishell  on   feature/builtins-base ⇡3 !2 
❯ ./minishell
DEBUG Minishell Start!

goteixei@minishell> unset GOOD_VAR WONT_BE_SET
goteixei@minishell> export GOOD_VAR=1 "BAD-VAR"=2 WONT_BE_SET=3
minishell: export: `BAD-VAR=2': not a valid identifier
goteixei@minishell> env | grep GOOD_VAR
GOOD_VAR=1
goteixei@minishell> env | grep WONT_BE_SET
WONT_BE_SET=3
goteixei@minishell> echo $?
0
goteixei@minishell>
```
