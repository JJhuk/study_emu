//
// Created by HaruGakkaP on 2020-11-23.
//

#include "Cartridge.h"
#include <fstream>
#include <algorithm>

void Cartridge::Load(std::string_view path)
{
	std::fstream file( path.data(), std::fstream::binary | std::fstream::in );
	if( !file.is_open() ) { throw std::logic_error("NO FILE");}

	std::vector<BYTE> buffer( (std::istreambuf_iterator<char>( file )), std::istreambuf_iterator<char>()  );
	if( buffer.empty() ) { throw std::logic_error("NO DATA"); }
	// 검증

	// 버퍼
	mBuffer = std::move( buffer );
}

std::string Cartridge::GetTitle()
{
	const size_t TITLE_START_POINT = 0x134;
	const size_t TITLE_END_POINT = 0x143;

	basicErrorCheck( TITLE_END_POINT );

	std::string name = std::string( &mBuffer[TITLE_START_POINT], &mBuffer[TITLE_END_POINT] );

	// Null 문자 제거
	name.erase( std::remove_if( name.begin(), name.end(), []( unsigned char c ) -> bool {
		return c == '\x00';
	} ), name.end() );

	return name;
}

Cartridge::ColorGameBoyFlag Cartridge::GetCGBFlag()
{
	constexpr size_t CGB_FLAG_POINT = 0x143;
	basicErrorCheck( CGB_FLAG_POINT );

	auto value = mBuffer[ CGB_FLAG_POINT ];
	auto rtn = ColorGameBoyFlag::CGB_UNKNOWN;

	switch ( value )
	{
		case 0x00:
			rtn = ColorGameBoyFlag::CGB_NONE;
			break;
		case 0x80:
			rtn = ColorGameBoyFlag::CGB_SUPPORT;
			break;
		case 0xC0:
			rtn = ColorGameBoyFlag::CGB_ONLY;
			break;
		default:
			break;
	}

	return rtn;
}

BYTE Cartridge::GetCartridgeType()
{
	constexpr size_t CARTRIDGE_TYPE_POINT = 0x147;
	basicErrorCheck( CARTRIDGE_TYPE_POINT );

	return mBuffer[ CARTRIDGE_TYPE_POINT ];
}

CartridgeSizeInfo Cartridge::GetSizeInfo()
{
	constexpr size_t SIZE_BASIC_INFOS [] = {
			32000, 64000, 128000, 256000, 512000, 1000000, 2000000, 4000000, 8000000
	};

	constexpr size_t BANK_BASIC_INFOS [] = {
			2, 4, 8, 16, 32, 64, 128, 256, 512
	};

	constexpr size_t SIZE_EXTEND_INFOS [] = {
			0, 0, 1100000, 1200000, 1500000
	};

	constexpr size_t BANK_EXTEND_INFOS [] = {
			0, 0, 72, 80, 96
	};

	constexpr size_t CARTRIDGE_TYPE_POINT = 0x147;
	basicErrorCheck( CARTRIDGE_TYPE_POINT );

	auto value = mBuffer[CARTRIDGE_TYPE_POINT];
	BYTE hi = (value & 0xf0u) >> 4u;
	BYTE lo = (value & 0x0fu);

	if( lo > 8 || ( hi == 5 ) && ( lo > 4 ) ) { throw  std::logic_error("WRONG SIZE INFO."); }

	size_t size = hi == 5 ? SIZE_EXTEND_INFOS[lo] : SIZE_BASIC_INFOS[lo];
	size_t bank = hi == 5 ? BANK_EXTEND_INFOS[lo] : BANK_BASIC_INFOS[lo];

	if( size == 0 || bank == 0 ) { throw std::logic_error("HI = 5, But Access to 1~2"); }

	CartridgeSizeInfo info;
	info.size = size;
	info.bank = bank;

	return info;
}

void Cartridge::basicErrorCheck(const size_t pos)
{
	if( mBuffer.empty() ) { throw std::logic_error("Cartridge Not INITED."); }
	if( mBuffer.size() <= pos ) { throw std::logic_error("NOT VALID CARTRIDGE."); }
}
