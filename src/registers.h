/**
* =============================================================================
* DynamicHooks
* Copyright (C) 2015 Robin Gohmert. All rights reserved.
* =============================================================================
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from 
* the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose, 
* including commercial applications, and to alter it and redistribute it 
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not 
* claim that you wrote the original software. If you use this software in a 
* product, an acknowledgment in the product documentation would be 
* appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*
* asm.h/cpp from devmaster.net (thanks cybermind) edited by pRED* to handle gcc
* -fPIC thunks correctly
*
* Idea and trampoline code taken from DynDetours (thanks your-name-here).
*/

#ifndef _REGISTERS_H
#define _REGISTERS_H


// ============================================================================
// >> INCLUDES
// ============================================================================
#include <stdlib.h>
#include <stdint.h>
#include <list>


// ============================================================================
// >> RegisterSize
// ============================================================================
enum RegisterSize : uint8_t {
	SIZE_INVALID = 0,
	SIZE_BYTE = 1,
	SIZE_WORD = 2,
	SIZE_DWORD = 4,
	SIZE_QWORD = 8,
	SIZE_TWORD = 10,
	SIZE_XMMWORD = 16,
	SIZE_YMMWORD = 32,
	SIZE_ZMMWORD = 64
};


// ============================================================================
// >> Register_t
// ============================================================================
enum Register_t
{
	// ========================================================================
	// >> 8-bit General purpose registers
	// ========================================================================
	AL,
	CL,
	DL,
	BL,
	AH,
	CH,
	DH,
	BH,

	// ========================================================================
	// >> 16-bit General purpose registers
	// ========================================================================
	AX,
	CX,
	DX,
	BX,
	SP,
	BP,
	SI,
	DI,

	// ========================================================================
	// >> 32-bit General purpose registers
	// ========================================================================
	EAX,
	ECX,
	EDX,
	EBX,
	ESP,
	EBP,
	ESI,
	EDI,

	// ========================================================================
	// >> 64-bit MM (MMX) registers
	// ========================================================================
	MM0,
	MM1,
	MM2,
	MM3,
	MM4,
	MM5,
	MM6,
	MM7,

	// ========================================================================
	// >> 128-bit XMM registers
	// ========================================================================
	XMM0,
	XMM1,
	XMM2,
	XMM3,
	XMM4,
	XMM5,
	XMM6,
	XMM7,

	// ========================================================================
	// >> 16-bit Segment registers
	// ========================================================================
	CS,
	SS,
	DS,
	ES,
	FS,
	GS,

	// ========================================================================
	// >> 80-bit FPU registers
	// ========================================================================
	ST0,
	ST1,
	ST2,
	ST3,
	ST4,
	ST5,
	ST6,
	ST7,
};


// ============================================================================
// >> CRegister
// ============================================================================
class CRegister
{
public:
	CRegister(int iSize)
	{
		m_iSize = iSize;
		m_pAddress = malloc(iSize);
	}

	~CRegister()
	{
		free(m_pAddress);
	}

	template<class T>
	T GetValue()
	{
		return *(T *) m_pAddress;
	}

	template<class T>
	T GetPointerValue(int iOffset=0)
	{
		return *(T *) (GetValue<unsigned long>() + iOffset);
	}

	template<class T>
	void SetValue(T value)
	{
		*(T *) m_pAddress = value;
	}

	template<class T>
	void SetPointerValue(T value, int iOffset=0)
	{
		*(T *) (GetValue<unsigned long>() + iOffset) = value;
	}

public:
	int m_iSize;
	void* m_pAddress;
};


// ============================================================================
// >> CRegisters
// ============================================================================
class CRegisters
{
public:
	CRegisters(std::list<Register_t> registers);
	~CRegisters();

private:
	CRegister* CreateRegister(std::list<Register_t>& registers, Register_t reg, int iSize);
	void DeleteRegister(CRegister* pRegister);

public:
	// ========================================================================
	// >> 8-bit General purpose registers
	// ========================================================================
	CRegister* m_al;
	CRegister* m_cl;
	CRegister* m_dl;
	CRegister* m_bl;
	CRegister* m_ah;
	CRegister* m_ch;
	CRegister* m_dh;
	CRegister* m_bh;

	// ========================================================================
	// >> 16-bit General purpose registers
	// ========================================================================
	CRegister* m_ax;
	CRegister* m_cx;
	CRegister* m_dx;
	CRegister* m_bx;
	CRegister* m_sp;
	CRegister* m_bp;
	CRegister* m_si;
	CRegister* m_di;

	// ========================================================================
	// >> 32-bit General purpose registers
	// ========================================================================
	CRegister* m_eax;
	CRegister* m_ecx;
	CRegister* m_edx;
	CRegister* m_ebx;
	CRegister* m_esp;
	CRegister* m_ebp;
	CRegister* m_esi;
	CRegister* m_edi;

	// ========================================================================
	// >> 64-bit MM (MMX) registers
	// ========================================================================
	CRegister* m_mm0;
	CRegister* m_mm1;
	CRegister* m_mm2;
	CRegister* m_mm3;
	CRegister* m_mm4;
	CRegister* m_mm5;
	CRegister* m_mm6;
	CRegister* m_mm7;

	// ========================================================================
	// >> 128-bit XMM registers
	// ========================================================================
	CRegister* m_xmm0;
	CRegister* m_xmm1;
	CRegister* m_xmm2;
	CRegister* m_xmm3;
	CRegister* m_xmm4;
	CRegister* m_xmm5;
	CRegister* m_xmm6;
	CRegister* m_xmm7;

	// ========================================================================
	// >> 16-bit Segment registers
	// ========================================================================
	CRegister* m_cs;
	CRegister* m_ss;
	CRegister* m_ds;
	CRegister* m_es;
	CRegister* m_fs;
	CRegister* m_gs;

	// ========================================================================
	// >> 80-bit FPU registers
	// ========================================================================
	CRegister* m_st0;
	CRegister* m_st1;
	CRegister* m_st2;
	CRegister* m_st3;
	CRegister* m_st4;
	CRegister* m_st5;
	CRegister* m_st6;
	CRegister* m_st7;
};

#endif // _REGISTERS_H
