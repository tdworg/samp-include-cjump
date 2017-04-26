#include <a_samp>

#include "tdw_cjump\tdw_cjump"

main()
{
	start0();
	start1();
}

const ITER = 10;

start0()
{
	new
		jumpbuffer[JmpBuf],
		retval,ccc;
	setjmp(jumpbuffer, retval);

	if (retval < ITER) {
		loop0(jumpbuffer, retval,ccc);
	}
}

loop0(jmp[JmpBuf], val, ccc)
{
	printf("%d", val++);
	longjmp(jmp, val);
}

new
	jumpbuffer1[JmpBuf];

start1()
{
	new
		retval;
	setjmp(jumpbuffer1, retval);

	if (retval < ITER) {
		loop1(retval);
	}
}

loop1(val)
{
	printf("%d", val++);
	longjmp(jumpbuffer1, val);
}
