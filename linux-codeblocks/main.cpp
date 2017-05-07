#include "lua.hpp"
#include <stdlib.h>
#include <string>

int lua_msgbox(lua_State* L) {
	const char* message = luaL_checkstring(L, 1);
	const char* caption = luaL_optstring(L, 2, "ShiVa Editor Message");

	std::string cppmsg(message);
	std::string cppcap(caption);
	std::string zstart("zenity --info --text='");
	std::string zmid1("' --title='");
	std::string zend("' &");

	std::string out = zstart +cppmsg +zmid1 +cppcap +zend;

	auto result = system( out.c_str() );

	lua_pushnumber(L, result);
	return 0;
}

extern "C" {

int /*__declspec(dllexport)*/ libinit (lua_State* L) {
	lua_register(L, "msgbox",  lua_msgbox);

	return 0;
}

}
