# Testing Export

## Setup

```bash
unset TEST_VAR LOCAL_VAR EMPTY_VAR VAR1 VAR2
echo "Setup complete. Environment is ready."
```

## Display Functionality

### Test 1

```bash
export
```

### Test 2

```bash
export TEST_VAR="hello world"
env | grep "TEST_VAR="
export | grep "TEST_VAR="
```

### Test 3

```bash
LOCAL_VAR="is now exported" #! how should this work????
env | grep "LOCAL_VAR"
export LOCAL_VAR
env | grep "LOCAL_VAR="
```

### Test 4

Update var name

```bash
export TEST_VAR="new value"
env | grep "TEST_VAR="
```

### Test 5

```bash
export VAR1=a VAR2=b
env | grep "VAR1="
env | grep "VAR2="
```

## Edge Cases

### Test 1

```bash
export EMPTY_VAR=""
env | grep "EMPTY_VAR="
export | grep "EMPTY_VAR="
```

### Test 2

```bash
export PATH+=":/new/path" # !TODO ???????
echo $PATH | grep ":/new/path"
```

### Test 3

```bash
export NO_VALUE_VAR

# 1. It should NOT be in `env`'s output
env | grep "NO_VALUE_VAR" # Expected: No output

# 2. It SHOULD be in `export`'s output
export | grep "NO_VALUE_VAR"
```

## Error Handling

### Test 1

Variable starts with a number

```bash
export 1BAD="oops"
echo $?
```

### Test 2

Invalid characters

```bash
export "BAD-VAR"="oops"
echo $?
```

### Test 2

```bash
export GOOD_VAR=1 "BAD-VAR"=2 WONT_BE_SET=3

# Verification
# 1. Check that GOOD_VAR was set
env | grep "GOOD_VAR="
# 2. Check 
env | grep "WONT_BE_SET" #should be set
# 3. Check the exit code
echo $?
```

CHECK WONT_BE_SET -> SHOULD BE SET

## Cleanup

```bash
unset TEST_VAR LOCAL_VAR EMPTY_VAR NO_VALUE_VAR VAR1 VAR2 GOOD_VAR
```

>NEEDS REVIEW



## More tests

```bash
export test="a  bc        def"
```

```bash
NEW_VAR=" -l "

echo $NEW_VAR
```

```bash
export NEW_VAR=" -l |"

export | grep NEW_VAR
```

```bash
goteixei@minishell> export a='$a'
goteixei@minishell> echo $a
$a
goteixei@minishell> export a="$a"
goteixei@minishell> echo $a
$a
goteixei@minishell> export b="$b"
goteixei@minishell> echo $b

goteixei@minishell> echo ola $b adeus
ola adeus
```
everything ok
