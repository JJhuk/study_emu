//
// Created by ffdd270 on 2020-05-20.
//

#include "../Chip8.h"



// [if]
//SE (Skip if Equal) Vx, Byte( 같으면_건너띄기 Vx Byte ).Vx =  X. Byte = KK.
void Chip8::opCode3XKK(WORD opCode)
{
	WORD index = (opCode & 0x0F00) >> 8;
	if(mRegisters[index] == (opCode & 0x00FF))
	{
		mProgramCounter+=2;
	}
}

// [if]
//SNE (Skip if not Equal) Vx, Byte (같지_않으면_건너띄기 Vx Byte )  Vx = X. Byte = KK,
void Chip8::opCode4XKK(WORD opCode)
{
	WORD index = (opCode & 0x0F00) >> 8;
	if(mRegisters[index] != (opCode & 0x00FF))
	{
		mProgramCounter += 2;
	}
}

// [if]
//SE (Skip if Equal ) Vx, Vy ( 같으면_건너띄기  Vx Vy ). Vx =  X, Vy = Y
void Chip8::opCode5XY0(WORD opCode)
{
	WORD indexVx = (opCode & 0x0F00) >> 8;
	WORD indexVy = (opCode & 0x00F0) >> 4;
	if(mRegisters[indexVx] == mRegisters[indexVy])
	{
		mProgramCounter += 2;
	}
}
