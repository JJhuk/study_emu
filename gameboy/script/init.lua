function init_script()
	TestUI:init()
	MemoryViewer:init()
	LoggerViewer:init()
	MemoryWatch:init()
	LuaCommander:init()
end



function table.shallow_copy( table, copy_target )
	for k, v in pairs( copy_target ) do
		table[k] = v
	end
end


ImGuiListClipperWarp = {}

function ImGuiListClipperWarp.Begin( self, clipper, item_count )
	clipper:Begin( item_count, -1 )
end


Util = {}

function Util.LogError( self, str )
	log_error( GetInstanceLogger(), tostring( str ) )
end


function Util.LogWarn( self, str )
	log_warning( GetInstanceLogger(), tostring( str ) )
end

function Util.LogInfo(  self, str )
	log_info( GetInstanceLogger(), tostring( str ) )
end

function info( str )
	Util:LogInfo( str )
end

function show_op_code( code )
	Util:LogInfo( GetInstanceCPU():TestOpCode( code ) )
end

function TRACE_BACK( err )
	Util:LogError( err )
end


ImGuiInputTextFlags_ = {
	None = 0,
	CharsHexadecimal = 1 << 1
}

local function _test_op_code_err( err  )
	local begin_index, end_index
	local inc = 0

	local str = err

	for i = 1, 9999 do -- 적당히 빠져 나오도록 =ㅁ=
		local find_begin, find_end  = string.find( str, "%d+" )

		if not find_begin then
			break
		end

		end_index = find_end + begin_index
		begin_index = find_begin + begin_index

		str = string.sub( str, find_begin )
	end

	if (not begin_index) or (not end_index) then return end

	local result = string.sub( err, begin_index, end_index )

	Util:LogError( err .. '  :'.. result ) -- TODO : 맨 마지막 글자만 따서 Hex로 뿌리기
end
function _test_op_code( code )
	GetInstanceCPU():TestOpCode( code )
end

function test_op_code( )
	for i = 0, 0xff do
		xpcall( _test_op_code, _test_op_code_err, i )
	end
end