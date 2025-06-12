# Parser Testing

## Quotes

```bash
echo $DISPLAY '$DISPLAY' "$DISPLAY" $$ $?
```

Expected result should be something like this:

```bash
:0 $DISPLAY :0 85395 0
```
