//
// Created by nhy20 on 2020-10-29.
//

#include "LuaContext.h"
#include "gameboy_luabinding.h"


LuaContext::LuaContext()
{
	init();
}

bool LuaContext::ExecuteFunction(std::string_view func_name)
{
	lua_getglobal( mLuaState, func_name.data() );

	if( !lua_isfunction( mLuaState, lua_gettop( mLuaState ) ) )
	{
		return false;
	}

	return ( lua_pcall( mLuaState, 0, 0, 0 ) == 0 );
}

bool LuaContext::ExecuteRefFunction(LuaContextRefId ref_id)
{
	if ( !IsCorrectKey( ref_id ) )
	{
		return false;
	}

	return false;
}

bool LuaContext::ExecuteString(std::string_view execute_string)
{
	if ( luaL_dostring( mLuaState, execute_string.data() ) ) // Return 있으면 문제가..
	{
		return false;
	}

	return true;
}


bool LuaContext::ExecuteFile(std::string_view file_path )
{
	if (luaL_dofile(mLuaState, file_path.data()))
	{
		return false;
	}

	return true;
}



bool LuaContext::IsExistGlobalValue(std::string_view value_name)
{
	lua_getglobal( mLuaState, value_name.data() );
	bool rtn = lua_isnil( mLuaState, -1 );
	lua_pop( mLuaState, 1 );
	return !rtn;
}

LuaContextRefId LuaContext::contextRefIdGenerate()
{
	uint64_t key = mReloadCnt & 0xffffu;
	uint64_t unique_id = mRefCnt & 0x0000ffffffffu;

	// 32비트 점프.
	uint64_t ref_id = ( key << 4u * 8u ) | unique_id;

	mRefCnt++;

	return ref_id;
}

bool LuaContext::IsCorrectKey(LuaContextRefId ref_id) const
{
	uint32_t key = ref_id & 0xffff00000000u; //상위 16비트
	uint32_t expect_key = mReloadCnt & 0xffffu;

	return key == expect_key;
}

LuaContextRefId LuaContext::MakeLuaCallback()
{
	LuaRefId ref_id = luaL_ref( mLuaState, LUA_REGISTRYINDEX );
	LuaContextRefId context_ref_id = contextRefIdGenerate();

	mReferenceMap.insert( std::make_pair( context_ref_id, ref_id ) );

	return context_ref_id;
}

void LuaContext::Reload()
{
	lua_close( mLuaState );
	mLuaState = nullptr;
	init();
}

std::string LuaContext::GetLastError()
{
	if ( !mLastError.empty() )
	{
		std::string return_value = mLastError;
		return mLastError;
	}

	const char * last_err = lua_tostring(mLuaState, -1);
	return last_err == nullptr ?  "" : last_err ;
}

void LuaContext::init()
{
	mRefCnt = 0;
	mReloadCnt++;
	mReferenceMap.clear();

	mLuaState = luaL_newstate();
	luaL_openlibs(mLuaState);

	gameboy_lua_binding(mLuaState);
}

LuaContext::~LuaContext()
{
	lua_close( mLuaState );
}
