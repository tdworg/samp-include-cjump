/** ======================================================================== **\
	C Jumps

| Description:

| Version:
	1.0.0

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
	jhea,  // heap ptr.
	jfrm,  // frame ptr.
	jstk,  // stack ptr.
	jjump  // the instruction pointer to the return address
};

stock setjmp(env[JmpBuf])
{
	#emit load.s.alt env
	#emit const.pri jhea
	#emit idxaddr
	#emit move.alt
	#emit lctrl 2
	#emit stor.i

	#emit load.s.alt env
	#emit const.pri jfrm
	#emit idxaddr
	#emit move.alt
	#emit load.s.pri 0
	#emit stor.i

	#emit lctrl 4
	#emit const.alt 12
	#emit sub
	#emit push.pri
	#emit load.s.alt env
	#emit const.pri jstk
	#emit idxaddr
	#emit move.alt
	#emit pop.pri
	#emit stor.i

	#emit load.s.alt env
	#emit const.pri jjump
	#emit idxaddr
	#emit move.alt
	#emit load.s.pri 4
	#emit stor.i

	return 0;
}

stock longjmp(env[JmpBuf]/*, val (see below) */)
{
	#emit load.s.alt env
	#emit const.pri jfrm
	#emit lidx
	#emit sctrl 5

	#emit const.pri jhea
	#emit lidx
	#emit sctrl 2

	#emit const.pri jstk
	#emit lidx
	#emit sctrl 4

	#emit const.pri jjump
	#emit lidx
	// We can't return values because to return the values we MUST use the PRI.
	#emit sctrl 6

	return 0;  // make compiler happy
}