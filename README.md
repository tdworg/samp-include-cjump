# TDW C-like jumps

This library adds the functional to jump between functions.

## Example:
```pawn
new jmp[JmpBuf];

main() {
	new ret;
	setjmp(jmp, ret);

	if (ret < 10) {
		somefunc(ret);
	}
}

somefunc(ret)
{
	printf("%d", ret);
	longjmp(jmp, ++ret);
}
```
