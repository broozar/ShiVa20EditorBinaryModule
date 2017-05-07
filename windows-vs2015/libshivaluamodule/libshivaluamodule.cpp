// libshivaluamodule.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "lua.hpp"

#include <ctime>
#include <stdlib.h>


///////////////////////////////////////////////////////////////////////////////
// HELPERS
///////////////////////////////////////////////////////////////////////////////

wchar_t globbuf[4096];

wchar_t * convertCharArrayToLPCWSTR(const char* charArray) {
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void setfieldNumber(lua_State* L, const char *index, float value) {
	lua_pushstring(L, index);
	lua_pushnumber(L, value);
	lua_settable(L, -3);
}


///////////////////////////////////////////////////////////////////////////////
// API
///////////////////////////////////////////////////////////////////////////////

/* Pop-up a Windows message box with your choice of message and caption */
int lua_msgbox(lua_State* L) {
	const char* message = luaL_checkstring(L, 1);
	const char* caption = luaL_optstring(L, 2, "ShiVa 2.0 Editor");
	auto lmessage = convertCharArrayToLPCWSTR(message);
	auto lcaption = convertCharArrayToLPCWSTR(caption);
	
	int result = MessageBox(NULL, lmessage, lcaption, MB_OK);
	lua_pushnumber(L, result);

	delete lmessage, lcaption;
	return 1;
}


///////////////////////////////////////////////////////////////////////////////
// MORE EXAMPLES - DELETE IN YOUR OWN LIB
///////////////////////////////////////////////////////////////////////////////

/* // calculate a sum of 2 numbers
int lua_calcsum(lua_State* L) {			// args need to be accessed by their index:
	auto num1 = luaL_checknumber(L, 1);	// arg 1
	auto num2 = luaL_checknumber(L, 2);	// arg 2
	auto sum = num1 + num2;

	lua_pushnumber(L, sum);

	return 1;
} */

/* // a function with 3 return values, Lua-style
int lua_multitime(lua_State* L) {
	auto t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	lua_pushnumber(L, now.tm_hour);	// return 1
	lua_pushnumber(L, now.tm_min);	// return 2
	lua_pushnumber(L, now.tm_sec);	// return 3

	return 3; // the number of returns needs to be indicated here
} */

/* // return values as associative table
int lua_multitimeAssocTable(lua_State* L) {
	auto t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	lua_newtable(L);
	setfieldNumber(L, "h", now.tm_hour);
	setfieldNumber(L, "m", now.tm_min);
	setfieldNumber(L, "s", now.tm_sec);

	return 1;
} */

/* // arbitary number of input parameters
int lua_genericsafesum(lua_State* L) {

	int n = lua_gettop(L);				// number of arguments
	lua_Number sum = 0;					// store result here
	int i;								// FOR counter
	for (i = 1; i <= n; i++) {
		if (!lua_isnumber(L, i)) {		// make sure we only accept numbers
			lua_pushstring(L, "incorrect argument");
			lua_error(L);				// stop interpreter, exit with error
		}
		sum += lua_tonumber(L, i);		// convert arg to num and add to sum
	}
	lua_pushnumber(L, sum);				// return overall sum

	return 1;
} */


///////////////////////////////////////////////////////////////////////////////
// INIT
///////////////////////////////////////////////////////////////////////////////

extern "C" {

	int __declspec(dllexport) libinit(lua_State* L) {
		lua_register(L, "msgbox", lua_msgbox);

		return 0;
	}

}


