# Command Execution Testing

## Setup

```bash
# Create a directory for our test scripts
mkdir -p test_scripts

# Create a simple, executable script
echo '#!/bin/bash' > test_scripts/hello.sh
echo 'echo "Hello from script!"' >> test_scripts/hello.sh
chmod +x test_scripts/hello.sh

# Create an identical script but with NO execute permissions
echo '#!/bin/bash' > test_scripts/no_perm.sh
echo 'echo "You should not see this!"' >> test_scripts/no_perm.sh
chmod -x test_scripts/no_perm.sh # Remove execute permission

# Create a file for grep to search in
echo "a line with the word apple" > test_scripts/data.txt
echo "a line with the word banana" >> test_scripts/data.txt

echo "Setup complete. Currently in:"
pwd
```

## Testing

### Test 1

```bash
ls
```

### Test 2

```bash
ls -l test_scripts
```

### Test 3 - Absolute Path

```bash
/bin/echo "This was called via absolute path"
```

Expected Output: This was called via absolute path

### Test 4 - Relative Path

```bash
./test_scripts/hello.sh
```

Expected Output: Hello from script!

### Test 5 - Command success

```bash
/bin/true
echo $?
```

Expected echo $? Output: 0

### Test 6 - Command failure

```bash
/bin/false
echo $?
```

Expected echo $? Output: 1

### Test 7 - grep finds a match

```bash
grep apple test_scripts/data.txt
echo $?
```

Expected grep Output: a line with the word apple
Expected echo $? Output: 0

### Test 8 - grep finds no match

```bash
grep orange test_scripts/data.txt
echo $?
```

Expected grep Output: No output.
Expected echo $? Output: 1

## Error Handling

### Test 1

```bash
thiscommanddoesnotexist
echo $?
```

Expected Output Message: minishell: thiscommanddoesnotexist: command not found
Expected echo $? Output: 127

### Test 2 - Path is a directory

```bash
./test_scripts
echo $?
```

Expected Output Message: minishell: ./test_scripts: is a directory
Expected echo $? Output: 126

### Test 3 - Permission denied

```bash
./test_scripts/no_perm.sh
echo $?
```

Expected Output Message: minishell: ./test_scripts/no_perm.sh: Permission denied
Expected echo $? Output: 126

## Cleanup

```bash
rm -rf test_scripts
```
