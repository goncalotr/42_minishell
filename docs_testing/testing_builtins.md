


## Env

### Useful Commands

### Testing
```sh
env
```

```sh
env foo
```


## 

### unset

1. Setup: Create some variables

```sh
# In your minishell prompt:
export MYVAR=testvalue
export ANOTHERVAR=12345
export VAR_TO_KEEP=safe
export MULTI_VAR_1=one
export MULTI_VAR_2=two
env | grep MYVAR         # Verify MYVAR=testvalue is there
env | grep ANOTHERVAR   # Verify ANOTHERVAR=12345 is there
```


```sh
unset ANOTHERVAR MULTI_VAR_1 NONEXISTENT_AGAIN MULTI_VAR_2
echo $?                # Expected output: 0
env | grep ANOTHERVAR   # Expected output: (nothing)
env | grep MULTI_VAR_1  # Expected output: (nothing)
env | grep MULTI_VAR_2  # Expected output: (nothing)
env | grep VAR_TO_KEEP  # Expected output: VAR_TO_KEEP=safe (verify it wasn't removed)
```

#### Test: Invalid identifier(s)

```sh
# In your minishell prompt:
export STILL_VALID=yes
unset 1INVALID           # Invalid: starts with number
# Expected stderr output: minishell: unset: `1INVALID': not a valid identifier
echo $?                # Expected output: 1

unset -INVALID          # Invalid: contains hyphen
# Expected stderr output: minishell: unset: `-INVALID': not a valid identifier
echo $?                # Expected output: 1

unset ""                # Invalid: empty string
# Expected stderr output: minishell: unset: `': not a valid identifier
echo $?                # Expected output: 1

unset STILL_VALID 9BAD BAD-NAME ALSO_VALID
# Expected stderr output: minishell: unset: `9BAD': not a valid identifier
# Expected stderr output: minishell: unset: `BAD-NAME': not a valid identifier
echo $?                # Expected output: 1 (because at least one was invalid)
env | grep STILL_VALID  # Expected output: (nothing) - should still unset valid ones
env | grep ALSO_VALID   # Expected output: (nothing) - should still unset valid ones
```

#### No arguments

```sh
unset
echo $?  
```