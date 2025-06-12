# PWD Testing

## Setup
```bash
mkdir -p /tmp/pwd_test_dir
cd /tmp/pwd_test_dir
```

## Testing

### Test 1

```bash
```

### Test 2

```bash
pwd
```

### Test 2

```bash
cd /
pwd
```

### Test 3

```bash
cd
pwd
```

### Test 4

```bash
cd /tmp/pwd_test_dir
pwd

# change terminal
rmdir /tmp/pwd_test_dir

# go back to the original termianl
pwd
echo $? #expected: 1
```

## Error Handling

### Test 1

pwd should not accept arguments

```bash
pwd some_argument
```

## Cleanup

```bash
cd /tmp
rm -rf pwd_test_dir
```
