# Echo Testing

## Simple Tests

### Test 1

```bash
echo test | cat -e
echo $?
```

### Test 2

```bash
echo | cat -e
echo $?
```

### Test 3

```bash
echo test1 test2 test3 test4 | cat -e
echo $?
```

### Test 4

```bash
echo test1 test2  test       test4	test5 | cat -e
echo $?
```

### Test 5

```bash
echo longstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstring | cat -e
echo $?
```

## Flag Tests

### Test 1

```bash
echo -n test1 test2 | cat -e
echo $?
```

### Test 2

```bash
echo -n -n -n test1 test2 | cat -e
echo $?
```

### Test 3

```bash
echo -nnn test1 test2 | cat -e
echo $?
```

Expected result:

```bash
goteixei@c2r5s1:~$ echo -nnn test1 test2 | cat -e
test1 test2goteixei@c2r5s1:~$ 
```

test above not working correctly

### Test 4

```bash
echo -nnnx test1 test2 | cat -e
```

Expected result:
```bash
goteixei@c2r5s1:~$ echo -nnnx test1 test2 | cat -e
-nnnx test1 test2$
```

### Test 5

```bash
echo -n -x test1 test2 | cat -e
```

### Test 6

```bash
echo - | cat -e
```

### Test 7

```bash
echo -n -n test1 test2 | cat -e
```

### Test 8

```bash
echo test1 -n test2 | cat -e
```

### Test 9

```bash
echo test1 -n -n test2 | cat -e
```

## Quote and Expansion Tests

Set variable
```bash
export TEST_VAR="start_test      test_end"
```

### Test 1

```bash
echo $TEST_VAR | cat -e
```

### Test 2

```bash
echo $var_doesnt_exist | cat -e
```

### Test 3

```bash
echo "$TEST_VAR" | cat -e
```

### Test 4

```bash
echo '$TEST_VAR' | cat -e
```

### Test 5

```bash
/bin/true
echo $? | cat -e
```

### Test 6

```bash
/bin/false
echo $? | cat -e
```
