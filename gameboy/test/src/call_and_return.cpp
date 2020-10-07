//
// Created by nhy20 on 2020-10-07.
//


#include <catch.hpp>
#include "GameboyCPU.h"
#include "util.h"

void check_call(GameboyCPU & cpu, CheckCondition check_condition, bool jp_ok  )
{
	WORD before_sp = cpu.GetRegisterSP().reg_16;
	WORD before_pc = cpu.GetRegisterPC().reg_16;

	CallResult result = callIfCondition( cpu, check_condition, 0x5260 );

	REQUIRE( ( result.reg_16_sp == ( before_sp - 2 ) ) == jp_ok );
	REQUIRE( ( result.reg_16_pc == 0x5260 ) == jp_ok );

	WORD saved_pc_value = static_cast<WORD>( static_cast<WORD>( cpu.GetMemoryValue(result.reg_16_sp + 1 ) ) << 8u ) | // hi
						  static_cast<WORD>( cpu.GetMemoryValue( result.reg_16_sp ) ); // lo.

	REQUIRE( ( saved_pc_value == ( before_pc + 1 ) ) == jp_ok ); // 한 스텝 진행했으니까..
}

void check_condition_ret(GameboyCPU & cpu, CheckCondition check_condition, bool rtn_ok, BYTE a_value )
{
	WORD before_sp = cpu.GetRegisterSP().reg_16;
	WORD before_pc = cpu.GetRegisterPC().reg_16;

	callWord( cpu, 0x5260 );
	cpu.SetInjectionCount( 0x5260 );
	subN(cpu, a_value, 1);

	REQUIRE( ( returnIfCondition( cpu, check_condition ) == before_pc + 1 ) == rtn_ok );
	REQUIRE( ( before_sp == cpu.GetRegisterSP().reg_16 ) == rtn_ok );
}

TEST_CASE( "CALL AND RETURN", "[CALL_AND_RETURN]")
{
	GameboyCPU cpu;

	SECTION("CALL WORD")
	{
		WORD before_sp = cpu.GetRegisterSP().reg_16;
		WORD before_pc = cpu.GetRegisterPC().reg_16;

		CallResult result = callWord( cpu, 0x2460 );

		REQUIRE( result.reg_16_sp == ( before_sp - 2 ) );
		REQUIRE( result.reg_16_pc == 0x2460 );

		WORD saved_pc_value = static_cast<WORD>( static_cast<WORD>( cpu.GetMemoryValue(result.reg_16_sp + 1 ) ) << 8u ) | // hi
				static_cast<WORD>( cpu.GetMemoryValue( result.reg_16_sp ) ); // lo.

		REQUIRE( saved_pc_value == ( before_pc + 1 ) ); // 한 스텝 진행했으니까..
	}

	SECTION("CALL cc, WORD")
	{
		SECTION("CALL C, WORD")
		{
			SECTION("OK")
			{
				subN(cpu, 0, 1);
				check_flags(cpu, false, true, true, true);
				check_call(cpu, CheckCondition::C, true); // OK.
			}

			SECTION("NOT OK")
			{
				subN(cpu, 2, 1);
				check_flags(cpu, false, false, true, false);
				check_call(cpu, CheckCondition::C, false); // NOT OK.
			}
		}

		SECTION("CALL NC, WORD")
		{
			SECTION("OK")
			{
				subN(cpu, 2, 1);
				check_flags(cpu, false, false, true, false);
				check_call(cpu, CheckCondition::NC, true); // OK.
			}

			SECTION("NOT OK")
			{
				subN(cpu, 0, 1);
				check_flags(cpu, false, true, true, true);
				check_call(cpu, CheckCondition::NC, false); // NOT OK.
			}
		}

		SECTION("CALL Z, WORD")
		{
			SECTION("OK")
			{
				subN(cpu, 1, 1);
				check_flags(cpu, true, false, true, false);
				check_call(cpu, CheckCondition::Z, true); // OK.
			}

			SECTION("NOT OK")
			{
				subN(cpu, 2, 1);
				check_flags(cpu, false, false, true, false);
				check_call(cpu, CheckCondition::Z, false); // NOT OK.
			}
		}

		SECTION("CALL NZ, WORD")
		{
			SECTION("OK")
			{
				subN(cpu, 2, 1);
				check_flags(cpu, false, false, true, false);
				check_call(cpu, CheckCondition::NZ, true); //  OK.
			}

			SECTION("NOT OK")
			{
				subN(cpu, 1, 1);
				check_flags(cpu, true, false, true, false);
				check_call(cpu, CheckCondition::NZ, false); // NOT OK.
			}
		}

		SECTION("RET")
		{
			WORD before_sp = cpu.GetRegisterSP().reg_16;
			WORD before_pc = cpu.GetRegisterPC().reg_16;

			callWord( cpu, 0x3242 );
			cpu.SetInjectionCount( 0x3242 );
			WORD ret_pc = returnInstruction( cpu );

			REQUIRE( ret_pc == before_pc + 1 ); // PC는 1늘었을테니..
			REQUIRE( before_sp == cpu.GetRegisterSP().reg_16 );
		}


		SECTION("RET cc")
		{
			SECTION("cc = C")
			{
				SECTION("OK")
				{
					check_condition_ret( cpu, CheckCondition::C, true, 0 );
					check_flags(cpu, false, true, true, true);
				}

				SECTION("NOT OK")
				{
					check_condition_ret( cpu, CheckCondition::C, false, 2 );
					check_flags(cpu, false, false, true, false);
				}
			}

			SECTION("cc = NC")
			{
				SECTION("OK")
				{
					check_condition_ret( cpu, CheckCondition::NC, true, 2 );
					check_flags(cpu, false, false, true, false);
				}

				SECTION("NOT OK")
				{
					check_condition_ret( cpu, CheckCondition::NC, false, 0 );
					check_flags(cpu, false, true, true, true);
				}
			}

			SECTION("cc = Z")
			{
				SECTION("OK")
				{
					check_condition_ret( cpu, CheckCondition::Z, true, 1 );
					check_flags(cpu, true, false, true, false);
				}

				SECTION("NOT OK")
				{
					check_condition_ret( cpu, CheckCondition::Z, false, 0 );
					check_flags(cpu, false, true, true, true);
				}
			}

			SECTION("cc = NZ")
			{
				SECTION("OK")
				{
					check_condition_ret( cpu, CheckCondition::NZ, true, 0 );
					check_flags(cpu, false, true, true, true);
				}

				SECTION("NOT OK")
				{
					check_condition_ret( cpu, CheckCondition::NZ, false, 1 );
					check_flags(cpu, true, false, true, false);
				}
			}
		}
	}
}