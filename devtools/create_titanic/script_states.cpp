/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

 // Disable symbol overrides so that we can use system headers.
#define FORBIDDEN_SYMBOL_ALLOW_ALL

// HACK to allow building with the SDL backend on MinGW
// see bug #3412 "TOOLS: MinGW tools building broken"
#ifdef main
#undef main
#endif // main

#include "file.h"
#include "script_states.h"

static const UpdateState12 BARBOT_STATES[] = {
	{ 0x0003AB24, 0x00000005, 0x00 },
	{ 0x0003AD33, 0x00000005, 0x00 },
	{ 0x0003AB40, 0x00000008, 0x00 },
	{ 0x0003AC6A, 0x00000008, 0x00 },
	{ 0x0003AB3E, 0x00000006, 0x00 },
	{ 0x0003AB3D, 0x00000006, 0x00 },
	{ 0x0003AB41, 0x00000007, 0x00 },
	{ 0x0003AB69, 0x00000008, 0x00 },
	{ 0x0003AE6D, 0x0000004E, 0x00 },
	{ 0x0003AC69, 0x0000004E, 0x00 },
	{ 0x0003AE6E, 0x0000004F, 0x00 },
	{ 0x0003AE6F, 0x00000051, 0x00 },
	{ 0x0003AE70, 0x00000051, 0x00 },
	{ 0x0003AE71, 0x00000051, 0x00 },
	{ 0x0003AE72, 0x00000051, 0x00 },
	{ 0x0003AE73, 0x00000051, 0x00 },
	{ 0x0003AE74, 0x00000051, 0x00 },
	{ 0x0003AE75, 0x00000051, 0x00 },
	{ 0x0003AE76, 0x00000051, 0x00 },
	{ 0x0003AE77, 0x00000051, 0x00 },
	{ 0x0003AEB8, 0x00000051, 0x00 },
	{ 0x0003AB20, 0x00000009, 0x00 },
	{ 0x0003AB14, 0x0000000A, 0x00 },
	{ 0x0003AB15, 0x0000000B, 0x00 },
	{ 0x0003AB16, 0x0000000C, 0x00 },
	{ 0x0003AB63, 0x0000000D, 0x00 },
	{ 0x0003AB64, 0x0000000D, 0x00 },
	{ 0x0003AB44, 0x00000001, 0x00 },
	{ 0x0003AB43, 0x00000001, 0x0B },
	{ 0x0003AB2A, 0x00000002, 0x00 },
	{ 0x0003AB4A, 0x00000003, 0x0B },
	{ 0x0003AB4C, 0x00000003, 0x0B },
	{ 0x0003AB65, 0x00000004, 0x00 },
	{ 0x0003AB2F, 0x0000000E, 0x00 },
	{ 0x0003AB30, 0x0000000F, 0x00 },
	{ 0x0003AB17, 0x00000010, 0x0B },
	{ 0x0003AB18, 0x00000010, 0x0B },
	{ 0x0003AAE3, 0x0000003E, 0x00 },
	{ 0x0003AAE4, 0x0000003E, 0x00 },
	{ 0x0003AAE5, 0x0000003E, 0x00 },
	{ 0x0003AB0F, 0x00000011, 0x00 },
	{ 0x0003AB11, 0x00000012, 0x00 },
	{ 0x0003AB12, 0x00000013, 0x00 },
	{ 0x0003AB13, 0x00000014, 0x00 },
	{ 0x0003AADC, 0x00000019, 0x00 },
	{ 0x0003AADD, 0x0000001A, 0x00 },
	{ 0x0003AADE, 0x0000001B, 0x00 },
	{ 0x0003AAFD, 0x00000015, 0x00 },
	{ 0x0003AAFE, 0x00000016, 0x00 },
	{ 0x0003AAFF, 0x00000017, 0x00 },
	{ 0x0003AB00, 0x00000018, 0x00 },
	{ 0x0003AAF4, 0x0000001C, 0x00 },
	{ 0x0003AAF5, 0x0000001D, 0x00 },
	{ 0x0003AAF6, 0x0000001E, 0x00 },
	{ 0x0003AAD9, 0x0000001F, 0x00 },
	{ 0x0003AADA, 0x00000020, 0x00 },
	{ 0x0003AADB, 0x00000021, 0x00 },
	{ 0x0003AAF7, 0x00000022, 0x00 },
	{ 0x0003AAF8, 0x00000023, 0x00 },
	{ 0x0003AAF9, 0x00000024, 0x00 },
	{ 0x0003AB04, 0x0000002C, 0x00 },
	{ 0x0003AB05, 0x0000002D, 0x00 },
	{ 0x0003AB06, 0x0000002E, 0x00 },
	{ 0x0003AADF, 0x00000029, 0x00 },
	{ 0x0003AAE0, 0x0000002A, 0x00 },
	{ 0x0003AAE1, 0x0000002B, 0x00 },
	{ 0x0003AB07, 0x00000038, 0x00 },
	{ 0x0003AB08, 0x00000039, 0x00 },
	{ 0x0003AB09, 0x0000003A, 0x00 },
	{ 0x0003AB01, 0x0000003B, 0x00 },
	{ 0x0003AB02, 0x0000003C, 0x00 },
	{ 0x0003AB03, 0x0000003D, 0x00 },
	{ 0x0003AAF0, 0x00000025, 0x00 },
	{ 0x0003AAF1, 0x00000026, 0x00 },
	{ 0x0003AAF2, 0x00000027, 0x00 },
	{ 0x0003AAF3, 0x00000028, 0x00 },
	{ 0x0003AB0A, 0x0000002F, 0x00 },
	{ 0x0003AB0B, 0x00000030, 0x00 },
	{ 0x0003AB0C, 0x00000031, 0x00 },
	{ 0x0003AB0D, 0x00000032, 0x00 },
	{ 0x0003AAEA, 0x00000033, 0x00 },
	{ 0x0003AAEB, 0x00000034, 0x00 },
	{ 0x0003AAEC, 0x00000035, 0x00 },
	{ 0x0003AAED, 0x00000036, 0x00 },
	{ 0x0003AAEE, 0x00000037, 0x00 },
	{ 0x0003ACC3, 0x0000003F, 0x00 },
	{ 0x0003ACC4, 0x00000040, 0x00 },
	{ 0x0003ACC5, 0x00000041, 0x00 },
	{ 0x0003ACC6, 0x00000042, 0x00 },
	{ 0x0003ACC7, 0x00000043, 0x00 },
	{ 0x0003ACC8, 0x00000044, 0x00 },
	{ 0x0003ADCF, 0x00000045, 0x00 },
	{ 0x0003ADD0, 0x00000046, 0x00 },
	{ 0x0003ADD1, 0x00000047, 0x00 },
	{ 0x0003ADD2, 0x00000048, 0x00 },
	{ 0x0003ADD3, 0x00000049, 0x00 },
	{ 0x0003ACA4, 0x0000004A, 0x00 },
	{ 0x0003ACA7, 0x0000004B, 0x00 },
	{ 0x0003ADD5, 0x0000004C, 0x00 },
	{ 0x0003AC7E, 0x0000004C, 0x00 },
	{ 0x0003ABF9, 0x0000004C, 0x00 },
	{ 0x0003AD14, 0x0000004C, 0x00 },
	{ 0x0003AD15, 0x0000004C, 0x00 },
	{ 0x0003AD10, 0x0000004C, 0x00 },
	{ 0x0003AD17, 0x0000004C, 0x00 },
	{ 0x0003AD21, 0x0000004C, 0x00 },
	{ 0x0003AD2F, 0x0000004C, 0x00 },
	{ 0x0003AC7F, 0x0000004D, 0x00 },
	{ 0x0003AEBA, 0x00000052, 0x0E },
	{ 0x0003AED5, 0x00000053, 0x00 },
	{ 0x0003B034, 0x00000054, 0x00 },
	{ 0x0003B037, 0x00000054, 0x00 },
	{ 0x0003B036, 0x00000055, 0x00 },
	{ 0x0003B035, 0x00000055, 0x00 },
	{ 0x0003B02D, 0x00000055, 0x00 },
	{ 0x0003B02F, 0x00000055, 0x00 },
	{ 0x0003B02E, 0x00000056, 0x00 },
	{ 0x0003B031, 0x00000056, 0x00 },
	{ 0x0003B033, 0x00000056, 0x00 },
	{ 0x0003B032, 0x00000057, 0x00 },
	{ 0x0003B023, 0x00000057, 0x00 },
	{ 0x0003B025, 0x00000057, 0x00 },
	{ 0x0003B024, 0x00000058, 0x00 },
	{ 0x0003B017, 0x00000058, 0x00 },
	{ 0x0003B01C, 0x00000058, 0x00 },
	{ 0x0003B01A, 0x00000059, 0x00 },
	{ 0x0003B01B, 0x0000005A, 0x00 },
	{ 0x0003B018, 0x0000005B, 0x00 },
	{ 0x0003B019, 0x0000005D, 0x00 },
	{ 0x0003B01D, 0x0000005D, 0x00 },
	{ 0x0003B01E, 0x0000005D, 0x00 },
	{ 0x0003B01F, 0x0000005D, 0x00 },
	{ 0x0003B026, 0x0000005D, 0x00 },
	{ 0x0003B027, 0x0000005D, 0x00 },
	{ 0x0003B028, 0x0000005D, 0x00 },
	{ 0x0003B029, 0x0000005D, 0x00 },
	{ 0x0003B030, 0x0000005D, 0x00 },
	{ 0x0003B02A, 0x0000005E, 0x00 },
	{ 0x0003ABF7, 0x0000005F, 0x00 },
	{ 0x0003AF6A, 0x00000060, 0x00 },
	{ 0x0003AEC6, 0x00000061, 0x00 },
	{ 0x00000000, 0x00000000, 0x00 }
};

static const UpdateState8 BELLBOT_STATES[] = {
	{ 0x00031070, 0x00000001 }, { 0x0003107B, 0x00000002 }, { 0x0003107E, 0x00000003 },
	{ 0x0003104F, 0x00000004 }, { 0x00030F23, 0x00000005 }, { 0x00030F2A, 0x00000006 },
	{ 0x00030F31, 0x00000007 }, { 0x00030F32, 0x00000007 }, { 0x00030F33, 0x00000007 },
	{ 0x00030F34, 0x00000007 }, { 0x00030F35, 0x00000007 }, { 0x00030F36, 0x00000007 },
	{ 0x00030F37, 0x00000008 }, { 0x00030F2E, 0x00000009 }, { 0x00030E78, 0x0000000A },
	{ 0x00030E42, 0x0000000C }, { 0x00030E0C, 0x0000000D }, { 0x00030E9C, 0x0000000E },
	{ 0x00030DC1, 0x0000000F }, { 0x00030DC2, 0x00000010 }, { 0x00030D6B, 0x00000011 },
	{ 0x00030D6C, 0x00000011 }, { 0x00030E1D, 0x00000012 }, { 0x00030E1E, 0x00000013 },
	{ 0x00030E3B, 0x00000014 }, { 0x00030EBA, 0x00000015 }, { 0x00031086, 0x00000016 },
	{ 0x000310A4, 0x00000017 }, { 0x00031058, 0x00000018 }, { 0x00031059, 0x00000019 },
	{ 0x00030E3F, 0x0000001A }, { 0x00030EBC, 0x0000001B }, { 0x00030E9B, 0x0000001C },
	{ 0x00030E32, 0x0000001D }, { 0x00030E76, 0x0000001E }, { 0x00031060, 0x0000001F },
	{ 0x00031065, 0x00000020 }, { 0x00031075, 0x00000021 }, { 0x00031077, 0x00000022 },
	{ 0x00031041, 0x00000023 }, { 0x00031038, 0x00000024 }, { 0x00030FAB, 0x00000025 },
	{ 0x00030FAF, 0x00000026 }, { 0x00030FB1, 0x00000027 }, { 0x00030FB8, 0x00000028 },
	{ 0x00030FB2, 0x00000029 }, { 0x00030FC1, 0x0000002A }, { 0x00030FC2, 0x0000002B },
	{ 0x00030FA4, 0x0000002C }, { 0x00030FA5, 0x0000002D }, { 0x00030FA7, 0x0000002E },
	{ 0x00030FA8, 0x0000002C }, { 0x00030FA6, 0x0000002C }, { 0x00030EAD, 0x0000002F },
	{ 0x00030EAE, 0x00000030 }, { 0x00030ED6, 0x00000031 }, { 0x00030ED7, 0x00000032 },
	{ 0x00030ED8, 0x00000033 }, { 0x000310A9, 0x00000034 }, { 0x00030F4C, 0x00000035 },
	{ 0x00030DA7, 0x00000036 }, { 0x00030D9F, 0x00000037 }, { 0x00030FC8, 0x00000038 },
	{ 0x00030FC9, 0x00000039 }, { 0x00030FCF, 0x0000003A }, { 0x00030FCA, 0x0000003B },
	{ 0x00030FCB, 0x0000003C }, { 0x00030FCC, 0x0000003D }, { 0x00030E41, 0x0000003E },
	{ 0x00030E12, 0x0000003F }, { 0x00030D72, 0x00000040 }, { 0x00030D76, 0x00000041 },
	{ 0x00030D78, 0x00000042 }, { 0x00030D79, 0x00000043 }, { 0x000310AE, 0x00000044 },
	{ 0x0003112C, 0x00000044 }, { 0x00031132, 0x00000045 }, { 0x00031133, 0x00000046 },
	{ 0x00031134, 0x00000047 }, { 0x000310D7, 0x00000048 }, { 0x0003113C, 0x00000049 },
	{ 0x0003113E, 0x0000004A }, { 0x0003113D, 0x0000004A }, { 0x00031146, 0x0000004B },
	{ 0x00031149, 0x0000004C }, { 0x0003114A, 0x0000004D }, { 0x0003114E, 0x0000004E },
	{ 0x00031151, 0x0000004E }, { 0x0003114F, 0x0000004E }, { 0x00031152, 0x0000004E },
	{ 0x0003115B, 0x0000004F }, { 0x00031163, 0x00000050 }, { 0x00031164, 0x00000051 },
	{ 0x00031165, 0x00000051 }, { 0x00031166, 0x00000051 }, { 0x00031167, 0x00000052 },
	{ 0x0003117A, 0x00000053 }, { 0x0003149A, 0x00000054 }, { 0x00031454, 0x00000055 },
	{ 0x0003157B, 0x00000056 }, { 0x00031177, 0x00000057 }, { 0x00031171, 0x00000057 },
	{ 0x0003117A, 0x00000057 }, { 0x00031507, 0x00000057 }, { 0x0003159D, 0x00000058 },
	{ 0x000315DD, 0x00000059 }, { 0x00031147, 0x0000005A }, { 0x00031148, 0x0000005A },
	{ 0x00000000, 0x00000000 }
};

static const UpdateState12 DESKBOT_STATES[] = {
	{ 0x0003AB24, 0x00000005, 0x00 },
	{ 0x0003AD33, 0x00000005, 0x00 },
	{ 0x0003AB40, 0x00000008, 0x00 },
	{ 0x0003AC6A, 0x00000008, 0x00 },
	{ 0x0003AB3E, 0x00000006, 0x00 },
	{ 0x0003AB3D, 0x00000006, 0x00 },
	{ 0x0003AB41, 0x00000007, 0x00 },
	{ 0x0003AB69, 0x00000008, 0x00 },
	{ 0x0003AE6D, 0x0000004E, 0x00 },
	{ 0x0003AC69, 0x0000004E, 0x00 },
	{ 0x0003AE6E, 0x0000004F, 0x00 },
	{ 0x0003AE6F, 0x00000051, 0x00 },
	{ 0x0003AE70, 0x00000051, 0x00 },
	{ 0x0003AE71, 0x00000051, 0x00 },
	{ 0x0003AE72, 0x00000051, 0x00 },
	{ 0x0003AE73, 0x00000051, 0x00 },
	{ 0x0003AE74, 0x00000051, 0x00 },
	{ 0x0003AE75, 0x00000051, 0x00 },
	{ 0x0003AE76, 0x00000051, 0x00 },
	{ 0x0003AE77, 0x00000051, 0x00 },
	{ 0x0003AEB8, 0x00000051, 0x00 },
	{ 0x0003AB20, 0x00000009, 0x00 },
	{ 0x0003AB14, 0x0000000A, 0x00 },
	{ 0x0003AB15, 0x0000000B, 0x00 },
	{ 0x0003AB16, 0x0000000C, 0x00 },
	{ 0x0003AB63, 0x0000000D, 0x00 },
	{ 0x0003AB64, 0x0000000D, 0x00 },
	{ 0x0003AB44, 0x00000001, 0x00 },
	{ 0x0003AB43, 0x00000001, 0x0B },
	{ 0x0003AB2A, 0x00000002, 0x00 },
	{ 0x0003AB4A, 0x00000003, 0x0B },
	{ 0x0003AB4C, 0x00000003, 0x0B },
	{ 0x0003AB65, 0x00000004, 0x00 },
	{ 0x0003AB2F, 0x0000000E, 0x00 },
	{ 0x0003AB30, 0x0000000F, 0x00 },
	{ 0x0003AB17, 0x00000010, 0x0B },
	{ 0x0003AB18, 0x00000010, 0x0B },
	{ 0x0003AAE3, 0x0000003E, 0x00 },
	{ 0x0003AAE4, 0x0000003E, 0x00 },
	{ 0x0003AAE5, 0x0000003E, 0x00 },
	{ 0x0003AB0F, 0x00000011, 0x00 },
	{ 0x0003AB11, 0x00000012, 0x00 },
	{ 0x0003AB12, 0x00000013, 0x00 },
	{ 0x0003AB13, 0x00000014, 0x00 },
	{ 0x0003AADC, 0x00000019, 0x00 },
	{ 0x0003AADD, 0x0000001A, 0x00 },
	{ 0x0003AADE, 0x0000001B, 0x00 },
	{ 0x0003AAFD, 0x00000015, 0x00 },
	{ 0x0003AAFE, 0x00000016, 0x00 },
	{ 0x0003AAFF, 0x00000017, 0x00 },
	{ 0x0003AB00, 0x00000018, 0x00 },
	{ 0x0003AAF4, 0x0000001C, 0x00 },
	{ 0x0003AAF5, 0x0000001D, 0x00 },
	{ 0x0003AAF6, 0x0000001E, 0x00 },
	{ 0x0003AAD9, 0x0000001F, 0x00 },
	{ 0x0003AADA, 0x00000020, 0x00 },
	{ 0x0003AADB, 0x00000021, 0x00 },
	{ 0x0003AAF7, 0x00000022, 0x00 },
	{ 0x0003AAF8, 0x00000023, 0x00 },
	{ 0x0003AAF9, 0x00000024, 0x00 },
	{ 0x0003AB04, 0x0000002C, 0x00 },
	{ 0x0003AB05, 0x0000002D, 0x00 },
	{ 0x0003AB06, 0x0000002E, 0x00 },
	{ 0x0003AADF, 0x00000029, 0x00 },
	{ 0x0003AAE0, 0x0000002A, 0x00 },
	{ 0x0003AAE1, 0x0000002B, 0x00 },
	{ 0x0003AB07, 0x00000038, 0x00 },
	{ 0x0003AB08, 0x00000039, 0x00 },
	{ 0x0003AB09, 0x0000003A, 0x00 },
	{ 0x0003AB01, 0x0000003B, 0x00 },
	{ 0x0003AB02, 0x0000003C, 0x00 },
	{ 0x0003AB03, 0x0000003D, 0x00 },
	{ 0x0003AAF0, 0x00000025, 0x00 },
	{ 0x0003AAF1, 0x00000026, 0x00 },
	{ 0x0003AAF2, 0x00000027, 0x00 },
	{ 0x0003AAF3, 0x00000028, 0x00 },
	{ 0x0003AB0A, 0x0000002F, 0x00 },
	{ 0x0003AB0B, 0x00000030, 0x00 },
	{ 0x0003AB0C, 0x00000031, 0x00 },
	{ 0x0003AB0D, 0x00000032, 0x00 },
	{ 0x0003AAEA, 0x00000033, 0x00 },
	{ 0x0003AAEB, 0x00000034, 0x00 },
	{ 0x0003AAEC, 0x00000035, 0x00 },
	{ 0x0003AAED, 0x00000036, 0x00 },
	{ 0x0003AAEE, 0x00000037, 0x00 },
	{ 0x0003ACC3, 0x0000003F, 0x00 },
	{ 0x0003ACC4, 0x00000040, 0x00 },
	{ 0x0003ACC5, 0x00000041, 0x00 },
	{ 0x0003ACC6, 0x00000042, 0x00 },
	{ 0x0003ACC7, 0x00000043, 0x00 },
	{ 0x0003ACC8, 0x00000044, 0x00 },
	{ 0x0003ADCF, 0x00000045, 0x00 },
	{ 0x0003ADD0, 0x00000046, 0x00 },
	{ 0x0003ADD1, 0x00000047, 0x00 },
	{ 0x0003ADD2, 0x00000048, 0x00 },
	{ 0x0003ADD3, 0x00000049, 0x00 },
	{ 0x0003ACA4, 0x0000004A, 0x00 },
	{ 0x0003ACA7, 0x0000004B, 0x00 },
	{ 0x0003ADD5, 0x0000004C, 0x00 },
	{ 0x0003AC7E, 0x0000004C, 0x00 },
	{ 0x0003ABF9, 0x0000004C, 0x00 },
	{ 0x0003AD14, 0x0000004C, 0x00 },
	{ 0x0003AD15, 0x0000004C, 0x00 },
	{ 0x0003AD10, 0x0000004C, 0x00 },
	{ 0x0003AD17, 0x0000004C, 0x00 },
	{ 0x0003AD21, 0x0000004C, 0x00 },
	{ 0x0003AD2F, 0x0000004C, 0x00 },
	{ 0x0003AC7F, 0x0000004D, 0x00 },
	{ 0x0003AEBA, 0x00000052, 0x0E },
	{ 0x0003AED5, 0x00000053, 0x00 },
	{ 0x0003B034, 0x00000054, 0x00 },
	{ 0x0003B037, 0x00000054, 0x00 },
	{ 0x0003B036, 0x00000055, 0x00 },
	{ 0x0003B035, 0x00000055, 0x00 },
	{ 0x0003B02D, 0x00000055, 0x00 },
	{ 0x0003B02F, 0x00000055, 0x00 },
	{ 0x0003B02E, 0x00000056, 0x00 },
	{ 0x0003B031, 0x00000056, 0x00 },
	{ 0x0003B033, 0x00000056, 0x00 },
	{ 0x0003B032, 0x00000057, 0x00 },
	{ 0x0003B023, 0x00000057, 0x00 },
	{ 0x0003B025, 0x00000057, 0x00 },
	{ 0x0003B024, 0x00000058, 0x00 },
	{ 0x0003B017, 0x00000058, 0x00 },
	{ 0x0003B01C, 0x00000058, 0x00 },
	{ 0x0003B01A, 0x00000059, 0x00 },
	{ 0x0003B01B, 0x0000005A, 0x00 },
	{ 0x0003B018, 0x0000005B, 0x00 },
	{ 0x0003B019, 0x0000005D, 0x00 },
	{ 0x0003B01D, 0x0000005D, 0x00 },
	{ 0x0003B01E, 0x0000005D, 0x00 },
	{ 0x0003B01F, 0x0000005D, 0x00 },
	{ 0x0003B026, 0x0000005D, 0x00 },
	{ 0x0003B027, 0x0000005D, 0x00 },
	{ 0x0003B028, 0x0000005D, 0x00 },
	{ 0x0003B029, 0x0000005D, 0x00 },
	{ 0x0003B030, 0x0000005D, 0x00 },
	{ 0x0003B02A, 0x0000005E, 0x00 },
	{ 0x0003ABF7, 0x0000005F, 0x00 },
	{ 0x0003AF6A, 0x00000060, 0x00 },
	{ 0x0003AEC6, 0x00000061, 0x00 },
	{ 0x00000000, 0x00000000, 0x00 }
};

static const UpdateState12 DOORBOT_STATES[] = {
	{ 0x00035BD0, 0x00000004, 0x06 },
	{ 0x00035BE7, 0x00000005, 0x00 },
	{ 0x00035BED, 0x00000006, 0x0A },
	{ 0x00035E41, 0x0000000C, 0x0A },
	{ 0x00035F9D, 0x0000000F, 0x00 },
	{ 0x00035F81, 0x00000010, 0x00 },
	{ 0x00035F82, 0x00000010, 0x00 },
	{ 0x00035F83, 0x00000010, 0x00 },
	{ 0x00035F84, 0x00000010, 0x00 },
	{ 0x00035F85, 0x00000010, 0x00 },
	{ 0x00035FC5, 0x00000011, 0x00 },
	{ 0x00035B6C, 0x00000021, 0x02 },
	{ 0x00035B6D, 0x00000022, 0x02 },
	{ 0x00035FCD, 0x00000012, 0x00 },
	{ 0x00035EF0, 0x00000020, 0x00 },
	{ 0x00035EF1, 0x00000020, 0x00 },
	{ 0x00035F0A, 0x00000020, 0x00 },
	{ 0x000362B0, 0x00000013, 0x00 },
	{ 0x000362B1, 0x00000013, 0x00 },
	{ 0x000362B2, 0x00000013, 0x00 },
	{ 0x000362B3, 0x00000013, 0x00 },
	{ 0x000362B4, 0x00000013, 0x00 },
	{ 0x000362B5, 0x00000013, 0x00 },
	{ 0x000362B9, 0x00000013, 0x00 },
	{ 0x000362BB, 0x00000013, 0x00 },
	{ 0x000362BA, 0x00000013, 0x00 },
	{ 0x000362BC, 0x00000013, 0x00 },
	{ 0x000362B8, 0x00000013, 0x00 },
	{ 0x000362BD, 0x00000013, 0x00 },
	{ 0x000362BE, 0x00000013, 0x00 },
	{ 0x000362BF, 0x00000013, 0x00 },
	{ 0x000362C0, 0x00000013, 0x00 },
	{ 0x000362C1, 0x00000013, 0x00 },
	{ 0x000362C2, 0x00000013, 0x00 },
	{ 0x000362B6, 0x00000014, 0x00 },
	{ 0x00035F8A, 0x00000015, 0x00 },
	{ 0x00036407, 0x00000016, 0x00 },
	{ 0x0003640C, 0x00000016, 0x00 },
	{ 0x0003641A, 0x00000016, 0x00 },
	{ 0x00036420, 0x00000016, 0x00 },
	{ 0x00036421, 0x00000016, 0x00 },
	{ 0x00036422, 0x00000016, 0x00 },
	{ 0x00036408, 0x00000016, 0x00 },
	{ 0x0003640A, 0x00000016, 0x00 },
	{ 0x0003640B, 0x00000016, 0x00 },
	{ 0x0003640D, 0x00000018, 0x00 },
	{ 0x00036415, 0x00000016, 0x00 },
	{ 0x00036416, 0x00000016, 0x00 },
	{ 0x00036417, 0x00000016, 0x00 },
	{ 0x00036418, 0x00000016, 0x00 },
	{ 0x00036419, 0x00000016, 0x00 },
	{ 0x0003640E, 0x00000016, 0x00 },
	{ 0x0003640F, 0x00000016, 0x00 },
	{ 0x00036410, 0x00000016, 0x00 },
	{ 0x00036411, 0x00000019, 0x00 },
	{ 0x00036412, 0x0000001A, 0x00 },
	{ 0x0003641B, 0x00000016, 0x00 },
	{ 0x0003641C, 0x00000016, 0x00 },
	{ 0x0003641D, 0x00000016, 0x00 },
	{ 0x0003641F, 0x00000016, 0x00 },
	{ 0x00035FF6, 0x0000001B, 0x00 },
	{ 0x00035FF7, 0x0000001C, 0x00 },
	{ 0x00035FF8, 0x0000001D, 0x00 },
	{ 0x00035FF9, 0x0000001E, 0x00 },
	{ 0x0003627F, 0x00000023, 0x00 },
	{ 0x00036280, 0x00000024, 0x00 },
	{ 0x00036281, 0x00000025, 0x00 },
	{ 0x00036282, 0x00000025, 0x00 },
	{ 0x00036457, 0x00000026, 0x00 },
	{ 0x00000000, 0x00000000, 0x00 }
};

static const UpdateState8 LIFTBOT_STATES[] = {
	{ 0x000335D6, 0x00000004 },
	{ 0x000337A7, 0x00000005 },
	{ 0x00033781, 0x00000006 },
	{ 0x0003381A, 0x00000009 },
	{ 0x0003381B, 0x00000009 },
	{ 0x0003381E, 0x00000009 },
	{ 0x0003381F, 0x00000009 },
	{ 0x00033820, 0x00000009 },
	{ 0x00033821, 0x00000009 },
	{ 0x00033822, 0x00000009 },
	{ 0x00033823, 0x00000009 },
	{ 0x00033824, 0x00000009 },
	{ 0x00033825, 0x00000009 },
	{ 0x0003381C, 0x00000009 },
	{ 0x0003381D, 0x00000009 },
	{ 0x00000000, 0x00000000 }
};

static const UpdateState8 MAITRED_STATES[] = {
	{ 0x0003F7D4, 0x00000002 },
	{ 0x0003F808, 0x00000003 },
	{ 0x0003F809, 0x00000009 },
	{ 0x0003F7F9, 0x00000009 },
	{ 0x0003F7D2, 0x00000009 },
	{ 0x0003F7F6, 0x00000004 },
	{ 0x0003F7D3, 0x00000005 },
	{ 0x0003F800, 0x00000006 },
	{ 0x0003F801, 0x00000007 },
	{ 0x0003F7FC, 0x00000008 },
	{ 0x0003F7FD, 0x00000008 },
	{ 0x0003F7F8, 0x00000008 },
	{ 0x0003F7FA, 0x00000008 },
	{ 0x0003F7F1, 0x0000000A },
	{ 0x0003F7F2, 0x0000000A },
	{ 0x0003F7F3, 0x0000000A },
	{ 0x0003F7F4, 0x0000000A },
	{ 0x0003F7F5, 0x0000000A },
	{ 0x0003F877, 0x0000000B },
	{ 0x0003FA55, 0x0000000C },
	{ 0x0003F863, 0x0000000C },
	{ 0x0003F864, 0x0000000C },
	{ 0x0003F865, 0x0000000C },
	{ 0x0003F866, 0x0000000D },
	{ 0x0003F867, 0x0000000E },
	{ 0x0003F86E, 0x0000000E },
	{ 0x0003F868, 0x0000000F },
	{ 0x0003F869, 0x0000000C },
	{ 0x0003F870, 0x00000010 },
	{ 0x0003F87C, 0x00000011 },
	{ 0x0003F87D, 0x00000011 },
	{ 0x0003F886, 0x00000012 },
	{ 0x0003F889, 0x00000013 },
	{ 0x0003F88A, 0x00000014 },
	{ 0x0003F88B, 0x00000015 },
	{ 0x0003F88C, 0x00000015 },
	{ 0x0003F88D, 0x00000016 },
	{ 0x0003F88E, 0x00000016 },
	{ 0x0003F895, 0x00000016 },
	{ 0x0003F893, 0x00000017 },
	{ 0x0003F89A, 0x00000018 },
	{ 0x0003F875, 0x00000019 },
	{ 0x0003F89C, 0x00000019 },
	{ 0x0003F8A3, 0x00000019 },
	{ 0x0003F8A2, 0x00000019 },
	{ 0x0003F89D, 0x0000001A },
	{ 0x0003F89E, 0x0000001A },
	{ 0x0003F89F, 0x0000001A },
	{ 0x0003F8A5, 0x0000001B },
	{ 0x0003F921, 0x0000001C },
	{ 0x0003F922, 0x0000001C },
	{ 0x0003FA56, 0x0000001E },
	{ 0x00000000, 0x00000000 }
};

void writeUpdateStates(const char *name, const UpdateState8 *states) {
	outputFile.seek(dataOffset);

	for (; states->_src; ++states) {
		outputFile.writeLong(states->_src);
		outputFile.writeLong(states->_dest);
	}

	uint size = outputFile.size() - dataOffset;
	writeEntryHeader(name, dataOffset, size);
	dataOffset += size;
}

void writeUpdateStates(const char *name, const UpdateState12 *states) {
	outputFile.seek(dataOffset);

	for (; states->_newId; ++states) {
		outputFile.writeLong(states->_newId);
		outputFile.writeLong(states->_newValue);
		outputFile.writeLong(states->_idMatch);
	}

	uint size = outputFile.size() - dataOffset;
	writeEntryHeader(name, dataOffset, size);
	dataOffset += size;
}

void writeAllUpdateStates() {
	writeUpdateStates("States/Barbot", BARBOT_STATES);
	writeUpdateStates("States/Bellbot", BELLBOT_STATES);
	writeUpdateStates("States/Deskbot", DESKBOT_STATES);
	writeUpdateStates("States/Doorbot", DOORBOT_STATES);
	writeUpdateStates("States/Liftbot", LIFTBOT_STATES);
	writeUpdateStates("States/MaitreD", MAITRED_STATES);

}
