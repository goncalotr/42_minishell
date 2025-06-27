# Env Testing

## Setup

```bash
# Set a standard variable
export TEST_VAR="A simple value"

# Set a variable with an equals sign in its value
export COMPLEX_VAR="KEY=VALUE"

# Set a variable with an empty value
export EMPTY_VAR=""

# Make sure a specific variable does not exist
unset NON_EXISTENT_VAR

echo "Setup complete. Environment is ready for testing."
```

## Testing

### Test 1

```bash
env
```

### Test 2

```bash
env | grep "USER="
```

### Test 3

```bash
env | grep "TEST_VAR="
```

### Test 4

```bash
env | grep "EMPTY_VAR="
```

### Test 5

```bash
env | grep "COMPLEX_VAR="
```

### Test 6

```bash
env | grep "NON_EXISTENT_VAR"
```

## Error Handling

```bash
env some_argument
echo $?
```

## Cleanup

```bash
unset TEST_VAR
unset COMPLEX_VAR
unset EMPTY_VAR
```

```env
env -i ./minishell
```
