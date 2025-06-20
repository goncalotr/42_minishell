
## Setup

Create a main test directory and some subdirectories

```bash
mkdir -p test_dir/subdir/another_subdir
```

Create a file

```bash
touch test_dir/a_file
```

Create a directory with no permissions

```bash
mkdir test_dir/no_perms
chmod 000 test_dir/no_perms
```

Start inside the main test directory

```bash
cd test_dir
echo "Setup complete. Currently in:"
pwd
```

## Basic Tests

### Test 1

```bash
cd /tmp
pwd
```

### Test 2

```bash
cd test_dir/subdir/another_subdir
cd subdir
pwd
```

## Testing

### Test 1

```bash
cd
pwd
```

### Test 2

```bash
cd ~
pwd
```

### Test 3

```bash
# Setup: Go somewhere to set OLDPWD
cd /tmp

# Action: Go back to the previous directory
cd -

# Verification: You should be back where you started
pwd
```

## Path Navigation Testing

### Test 1

```bash
cd ..
pwd
```

### Test 2

```bash
cd ../..
pwd
```

### Test 3

```bash
cd ../../subdir/./another_subdir
pwd
```

## Error Handling

### Test 1

```bash
cd this_dir_does_not_exist
echo $?
```

## Cleanup

```bash
rm -rf test_dir
```

26-06-16


## More Testing

```bash
cd ...
```
