//
// Created by HaruGakkaP on 2020-12-15.
//

#include "GPU.h"


GPU::GPU() : mMemory( { 0 } ), mLCDStatusRegister( 0 ), mLCDControlRegister( 0 )
{

}

constexpr size_t VRAM_START_ADDRESS = 0x8000;
// 0x8000~0x9fff
BYTE GPU::Get(size_t mem_addr) const
{
	checkAddress(mem_addr);
	return mMemory[mem_addr - VRAM_START_ADDRESS];
}


void GPU::Set(size_t mem_addr, BYTE value)
{
	if( mem_addr == 0xff40 ) // LCD Control Register
	{
		mLCDControlRegister = value;
	}
	else if( mem_addr == 0xff41 )
	{
		// 하위 3비트는 READ-ONLY 7번 비트는 존재하지 않음.
		mLCDStatusRegister = ( value & 0b01111000u );
	}
	else // VRAM
	{
		checkAddress(mem_addr);
		mMemory[mem_addr - VRAM_START_ADDRESS] = value;
	}

}

void GPU::checkAddress(size_t mem_addr) const
{
	int result_relative_address = static_cast<int>( mem_addr ) - static_cast<int>( VRAM_START_ADDRESS );

	if (result_relative_address < 0 ) { throw  std::logic_error("UNDERFLOW, ADDRESS"); }
	if (result_relative_address >= mMemory.size()) { throw std::logic_error("OVERFLOW, ADDRESS."); }

}

inline bool GetBit( BYTE origin, BYTE bit_pos )
{
	return ( origin & ( 0b1u << bit_pos ) ) >> bit_pos;
}

//LCD Control Register

bool GPU::IsLCDDisplayEnable()
{
	return GetBit( mLCDControlRegister, 7 ) == 1;
}

WORD GPU::GetSelectedWindowTileMap()
{
	return GetBit( mLCDControlRegister, 6 ) == 1 ?
		0x9C00u :
		0x9800u ;
}

bool GPU::IsWindowDisplayEnable()
{
	return GetBit( mLCDControlRegister, 5 ) == 1;
}

WORD GPU::GetSelectBGAndWindowTileData()
{
	return GetBit( mLCDControlRegister, 4 ) == 1 ?
		0x8000u :
		0x8800u ;
}

WORD GPU::GetSelectBGTileMapDisplay()
{
	return GetBit( mLCDControlRegister, 3 ) == 1 ?
		0x9C00u :
		0x9800u ;
}

bool GPU::IsSpriteSize()
{
	return GetBit( mLCDControlRegister, 2 ) == 1;
}

bool GPU::IsSpriteDisplayEnable()
{
	return GetBit( mLCDControlRegister, 1 ) == 1;
}

bool GPU::CheckProperty()
{
	return GetBit( mLCDControlRegister, 0 ) == 1;
}

//LCD Status Register

bool GPU::IsEnableLYCoincidenceInterrupt()
{
	return GetBit( mLCDStatusRegister, 6 ) == 1;
}

bool GPU::IsEnableMode2OAMInterrupt()
{
	return GetBit( mLCDStatusRegister, 5 ) == 1;
}

bool GPU::IsEnableMode1VBlankInterrupt()
{
	return GetBit( mLCDStatusRegister, 4 ) == 1;
}

bool GPU::IsEnableMode0HBlankInterrupt()
{
	return GetBit( mLCDStatusRegister, 3 ) == 1;
}

bool GPU::GettCoincidenceFlag()
{
	return GetBit( mLCDStatusRegister, 2 ) == 1;
}

BYTE GPU::GetModeFlag()
{
	BYTE bit1 = GetBit( mLCDStatusRegister, 1 );
	BYTE bit0 = GetBit( mLCDStatusRegister, 0 );

	return static_cast<BYTE>( bit1 << 1u ) | bit0 ;
}
