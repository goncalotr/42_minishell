# Minishell Testing - builtins

## 1 echo

Requirements:
- `-n` option

### Test Cases
#### Core Functionality & Arguments

No arguments

```sh
echo
> \n
```

Single argument

```sh
echo hello
> hello\n
```

Multiple arguments

```sh
echo hello world 123
> hello world 123\n
```

Arguments with multiple spaces between them

```sh
echo hello   world
> hello world\n
```

Multiple empty string arguments

```sh
echo ""
> \n
```

Multiple empty string arguments

```sh
echo "" ""
> \n
```

Mixed empty and non-empty arguments

```sh
echo hello "" world
> hello  world\n
```

#### -n Option Testing

Basic `-n`

```sh
echo -n hello
> helloNEXTPROMPT
```

`-n` with multiple arguments

```sh
echo -n hello world
> hello worldNEXTPROMPT
```

`-n` as the only argument

```sh
echo -n
> NEXTPROMPT
```

`-n` not as the first argument

```sh
echo hello -n world
> hello -n world\n
```

`-n` quoted

```sh
echo "-n" hello
> -n hello\n
```

Multiple `-n` flags

```sh
echo -n -n hello
> -n helloNEXTPROMPT
```

`-nnnn`

```sh
echo -nnnn hello
> helloNEXTPROMPT
```

`-nnnnx`
!TODO

```sh
echo -nnnnx hello
>
```

#### Quotes and Expansions

Single quotes

```sh
echo 'hello $USER'
> hello $USER\n
```

Double quotes

```sh
echo "hello $USER"
> hello <your_actual_username>\n
```

-n with quotes and expansion

```sh
echo -n "hello $USER"
> hello <your_actual_username>NEXTPROMPT
```

Variable evaluates to -n

```sh
VAR="-n"
echo $VAR hello
> -n hello\n
```

Variable evaluates to part of the string

```sh
VAR="world"
echo "hello $VAR"
> hello world\n
```

Empty variable

```sh
unset EMPTYVAR
echo $EMPTYVAR
> \n
```

Empty variable with other args

```sh
unset EMPTYVAR
echo hello$EMPTYVAR world
> hello world\n
```

Empty variable with -n

```sh
unset EMPTYVAR
echo -n $EMPTYVAR
> NEXTPROMPT
```

## 2 cd

Requirements:
- Change directory using only a relative or absolute path.
- Update PWD environment variable.
- Update OLDPWD environment variable.
- Handle errors gracefully.
- No options (-L, -P).
- No special handling for cd with no arguments (should not go to $HOME).
- No special handling for cd -.

### Setup Commands (Run before tests if needed)

```sh
mkdir /testing/minishell_cd_test
mkdir /testing/minishell_cd_test/subdir
touch /testing/minishell_cd_test/a_file
mkdir /testing/minishell_cd_test/no_perms
chmod 000 /testing/minishell_cd_test/no_perms
cd /testing
```

### Test Cases
#### Basic Success Cases

Absolute path

```sh
pwd
> /testing
cd /testing/minishell_cd_test
pwd
> /testing/minishell_cd_test\n
echo $PWD
> /testing/minishell_cd_test\n
echo $OLDPWD
> /testing\n
```

Relative path - subdirectory

```sh
pwd
> /testing/minishell_cd_test\n
cd subdir
pwd
> /testing/minishell_cd_test/subdir\n
echo $PWD
> /testing/minishell_cd_test/subdir\n
echo $OLDPWD
> /ttestingmp/minishell_cd_test\n
```

Relative path - parent directory

```sh
pwd
> /testing/minishell_cd_test/subdir\n
cd ..
pwd
> /testing/minishell_cd_test\n
echo $PWD
> /testing/minishell_cd_test\n
echo $OLDPWD
> /testing/minishell_cd_test/subdir\n
```
Path with .

```sh
```

### Error Handling

### Environment Variable Interaction


## 3 pwd

Requirements:
- Print the absolute path of the current working directory, followed by a newline.
- No options are supported or required (e.g., -L, -P).
- Must correctly reflect the directory changed by cd.
- Should handle cases where the current directory might have been removed externally.
- Should handle cases where $PWD might be unset or invalid.
- Should return status 0 on success, non-zero on failure.

### Setup Commands


### Test Cases

#### Basic Functionality

Simple case
```sh
pwd
> /tmp\n
# Check $? is 0
```

After cd
```sh
```

#### Environment Variable Interaction

PWD unset
```sh

```

PWD incorrect/invalid

```sh
```

#### Symbolic Link Handling


```sh
```

#### Error Handling


```sh
```

#### Cleanup


```sh
```


## 4 export

## 5 unset


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


## 6 env

```sh
env
```

```sh
env foo
```


## 7 exit
