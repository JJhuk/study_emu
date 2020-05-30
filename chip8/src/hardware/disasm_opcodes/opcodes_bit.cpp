#ifdef _CHIP8_DISASM_BUILD

//
// Created by ffdd270 on 2020-05-20.
//

#include "../Chip8.h"
#include "disasm_util.h"
// [bit]
//OR Vx, Vy .  Vx = Vx | Vy. 비트 OR 연산자.
void Chip8::opCode8XY1(WORD opCode)
{
	std::string comment = createComment_Registers( "OR", DecodeOpCodeSecond( opCode ), DecodeOpCodeThird( opCode) );
	pushDisasmString( opCodeToDisASMString( opCode, comment ) );
}

// [bit]
//AND Vx Vy .  Vx = Vx & Vy. 비트 AND 연산자 .
void Chip8::opCode8XY2(WORD opCode)
{
	std::string comment = createComment_Registers( "AND", DecodeOpCodeSecond( opCode ), DecodeOpCodeThird( opCode ) );
	pushDisasmString( opCodeToDisASMString( opCode, comment ) );
}

// [bit]
//XOR Vx Vy . Vx = Vx XOR Vy. 비트 XOR 연산자.
void Chip8::opCode8XY3(WORD opCode)
{
	std::string comment = createComment_Registers( "XOR", DecodeOpCodeSecond( opCode ), DecodeOpCodeThird( opCode) );
	pushDisasmString( opCodeToDisASMString( opCode, comment ) );
}

// [bit]
//SHR (SHfit Right) Vx {, Vy } Vx = Vx SHR 1 (혹은 y.).
//Vx의 최하위 비트가 1이면 VF는 1로 설정하고, 그렇지 않으면 0으로 설정. 그 다음, Vx는 2만큼 나눈다. ( 1비트씩 우로 밀렸으니까 )
void Chip8::opCode8XY6(WORD opCode)
{
	std::string comment = createComment_Registers( "SHR", DecodeOpCodeSecond( opCode ), DecodeOpCodeThird( opCode) );
	pushDisasmString( opCodeToDisASMString( opCode, comment ) );
}

// [bit]
//SHL(SHift Left) Vx, {Vy}. Vx = Vx SHL 1.
//Vx의 최상위 비트가 1이면 VF를 1로 설정. 아니라면 0. 그 후, Vx를 2만큼 곱해진다. ( 1비트씩 좌로 밀렸으니까 )
void Chip8::opCode8XYE(WORD opCode)
{
	std::string comment = createComment_Registers( "SHL", DecodeOpCodeSecond( opCode ), DecodeOpCodeThird( opCode) );
	pushDisasmString( opCodeToDisASMString( opCode, comment ) );
}

#endif