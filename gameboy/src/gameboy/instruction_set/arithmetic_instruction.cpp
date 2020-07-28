//
// Created by nhy20 on 2020-07-17.
//

#include "../GameboyCPU.h"


void GameboyCPU::commonCarryInstruction()
{
	if( GetFlagC() )
	{
		mRegisters.AF.hi += 1;
	}
}

void GameboyCPU::commonArithmeticFlagInit()
{
	resetFlags();
	setArithmeticFlags();
}

void GameboyCPU::commonAddRegAFromRegister(BYTE opCode)
{
	BYTE argument = 0b00000111 & opCode;
	BYTE & register_value = m8bitArguments[ argument ].ref;
	mRegisters.AF.hi += register_value;
}

void GameboyCPU::commonAddRegAFromImm8(BYTE opCode)
{
	mRegisters.AF.hi += immediateValue();
}

void GameboyCPU::commonAddRegAFromMemHL(BYTE opCode)
{
	mRegisters.AF.hi += mGameMemory[ mRegisters.HL.reg_16 ];
}


void GameboyCPU::commonSubRegAFromRegister(BYTE opCode)
{
	BYTE argument = 0b00000111 & opCode;
	BYTE & register_value = m8bitArguments[ argument ].ref;
	mRegisters.AF.hi -= register_value;
}

void GameboyCPU::commonSubRegAFromImm8(BYTE opCode)
{
	mRegisters.AF.hi -= immediateValue();
}

void GameboyCPU::commonSubRegAFromMemHL(BYTE opCode)
{
	mRegisters.AF.hi -= mGameMemory[ mRegisters.HL.reg_16 ];
}



//ADD A, r
// 0b10000rrr { rrr = 8bitArgument }
// A <- A + r
// = Flag =
// Z = if A is 0
// H = if bit 3 carry
// C = if bit 7 carry
// N = Reset
void GameboyCPU::addRegAFromRegister(BYTE opCode)
{
	commonAddRegAFromRegister( opCode );
	commonArithmeticFlagInit();
}


//ADD A, n
// 0b11000110 ( 0xC6 )
// A <- A + n
// imm8
// = Flag = ( Same as ADD A, r )
void GameboyCPU::addRegAFromImm8(BYTE opCode)
{
	commonAddRegAFromImm8( opCode );
	commonArithmeticFlagInit();
}

//ADD A, (HL)
// 0b10000110 ( 0x86 )
// = Flag = ( Same as ADD A, r )
void GameboyCPU::addRegAFromMemHL(BYTE opCode)
{
	commonAddRegAFromMemHL( opCode );
	commonArithmeticFlagInit();
}

//ADC A, r ( Add With Carry. if Carry Set. add + 1 from result value. )
// 0b10001rrr (r = m8BitArguments)
// = Flag = ( Same as ADD A, r )
void GameboyCPU::addRegAFromRegisterAndCarry(BYTE opCode)
{
	commonAddRegAFromRegister( opCode );
	commonCarryInstruction();
	commonArithmeticFlagInit();
}

//ADC A, n ( Add With Carry. if Carry Set. add + 1 from result value. )
// 0b11001110 ( 0xCE )
// 0bnnnnnnnn
// = Flag = ( Same as ADD A, r )
void GameboyCPU::addRegAFromImm8AndCarry(BYTE opCode)
{
	commonAddRegAFromImm8( opCode );
	commonCarryInstruction();
	commonArithmeticFlagInit();
}

//ADC A, (HL) (  Add With Carry. if Carry Set. add + 1 from result value. )
// 0b10001110 (0x8E)
// = Flag = ( Same as ADD A, r )
void GameboyCPU::addRegAFromMemHLAndCarry(BYTE opCode)
{
	commonAddRegAFromMemHL( opCode );
	commonCarryInstruction();
	commonArithmeticFlagInit();
}


//SUB r
// 0b10010rrr { r = m8BitArguments }
// = Flag = ( Same as ADD A, r )
void GameboyCPU::subRegAFromRegister(BYTE opCode)
{
	commonSubRegAFromRegister( opCode );
	commonArithmeticFlagInit();
}

//SUB n
// 0b11010110 (0xD6)
// 0bnnnnnnnn
// = Flag = ( Same as ADD A, r )
void GameboyCPU::subRegAFromImm8(BYTE opCode)
{
	commonSubRegAFromImm8( opCode );
	commonArithmeticFlagInit();
}

//SUB (HL)
// 0b10010110 (0x96)
// = Flag = ( Same as ADD A, r)
void GameboyCPU::subRegAFromMemHL(BYTE opCode)
{
	commonSubRegAFromMemHL( opCode );
	commonArithmeticFlagInit();
}
