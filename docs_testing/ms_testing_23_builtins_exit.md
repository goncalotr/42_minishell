# Exit Testing

Test pattern

```bash
echo "exit [args]" | ./minishell; echo $?
```

## Testing

### Test 1

```bash
echo "/bin/true; exit" | ./minishell; echo $?
```

### Test 2

```bash
echo "exit 42" | ./minishell; echo $?
```

### Test 3

```bash
echo "exit 0" | ./minishell; echo $?
```

### Test 4

```bash
echo "exit 255" | ./minishell; echo $?
```

## Edge Cases

### Test 1

```bash
echo "exit 256" | ./minishell; echo $?
```

### Test 2

```bash
echo "exit 300" | ./minishell; echo $?
```

### Test 3

```bash
echo "exit -1" | ./minishell; echo $?
```

## Error Handling

### Test 1

```bash
exit 1 2
echo $?

```

### Test 2

```bash
exit foobar
echo $?
```
