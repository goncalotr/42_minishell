# Echo Testing

## Simple Tests

### Test 1

```bash
echo test | cat -e
echo $?
```

20250612 OK

### Test 2

```bash
echo | cat -e
echo $?
```

20250612 OK

### Test 3

```bash
echo test1 test2 test3 test4 | cat -e
echo $?
```

20250612 OK

### Test 4

```bash
echo test1 test2  test       test4	test5 | cat -e
echo $?
```

with no tabs - 20250612 OK

how to test with tabs?
test with tabs - ???

### Test 5

```bash
echo longstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstringlongstring | cat -e
echo $?
```

20250612 OK

## Flag Tests

### Test 1

```bash
echo -n test1 test2 | cat -e
echo $?
```

20250612 OK

### Test 2

```bash
echo -n -n -n test1 test2 | cat -e
echo $?
```

20250612 OK

### Test 3

```bash
echo -nnn test1 test2 | cat -e
echo $?
```
2025-06-15 v

Expected result:

```bash
goteixei@c2r5s1:~$ echo -nnn test1 test2 | cat -e
test1 test2goteixei@c2r5s1:~$ 
```

test above not working correctly

2025-06-15 v

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

## Other

2025-06-16
random commands plus:
```bash
goteixei@minishell> echo -nn -nnx -n echo
--- DEBUG a_args ---
node->args[0]: "echo"
node->args[1]: "-nn"
node->args[2]: "-nnx"
node->args[3]: "-n"
node->args[4]: "echo"
node->args[5]: (NULL)
--- END DEBUG ---
-nnx -n echogoteixei@minishell> echo -nn ola
--- DEBUG a_args ---
node->args[0]: "echo"
node->args[1]: "-nn"
node->args[2]: "ola"
node->args[3]: (NULL)
--- END DEBUG ---
olamalloc_consolidate(): invalid chunk size
[1]    67574 IOT instruction (core dumped)  ./minishell
```

