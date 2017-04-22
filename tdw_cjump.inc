/** ======================================================================== **\
	C Jumps

| Description:

| Version:
	1.2.0

| License:
	Copyright (c) 2017 Double V

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgement in the product documentation would be
		appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
\** ======================================================================== **/

#if defined _inc_tdw_cjump
	#undef _inc_tdw_cjump
#endif

#if defined _TDW_C_JUMP
	#endinput
#endif

#define _TDW_C_JUMP

enum JmpBuf
{
	jhea,      // heap ptr.
	jfrm,      // frame ptr.
	jstk,      // stack ptr.
	jjump,     // the instruction pointer to the return address
	jretval,   // reference to the variable
	jlastfunc  // last function address (FRM)
};

stock setjmp(env[JmpBuf], &retval)
{
	static
		hea,
		frm,
		stk,
		rvip,
		rval;

	#emit lctrl 2
	#emit stor.pri hea

	#emit load.s.pri 0
	#emit stor.pri frm

	#emit lctrl 4
	#emit stor.pri stk

	#emit load.s.pri 4
	#emit stor.pri rvip

	#emit load.s.pri retval
	#emit stor.pri rval

	env[jfrm]    = frm;
	env[jhea]    = hea;
	env[jstk]    = stk;
	env[jjump]   = rvip;
	env[jretval] = rval;

	return 0;
}

stock longjmp(env[JmpBuf], val)
{
	static
		hea,
		frm,
		stk,
		rvip,
		rval,
		lfunc,
		addr,
		args;

	hea = env[jhea];
	frm = env[jfrm];
	stk = env[jstk];
	rvip = env[jjump];
	rval = env[jretval];
	lfunc = env[jlastfunc];

	#emit load.s.pri val
	#emit sref.pri rval

	#emit load.s.pri 0
	#emit stor.pri addr

	#emit add.c 8
	#emit load.i
	#emit stor.pri args

	if (addr != lfunc) {
		env[jlastfunc] = addr;
	}

	if (args > 4) {
		stk += args + 8;
	} {}

	#emit load.pri frm
	#emit sctrl 5

	#emit load.pri hea
	#emit sctrl 2

	#emit load.pri stk
	#emit sctrl 4

	#emit load.pri rvip
	#emit sctrl 6

	return 0;  // make compiler happy
}
