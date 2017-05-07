/*
 *  shivaluamodule.cpp
 *  shivaluamodule
 *
 *  Created by Felix Caffier on 07.05.17.
 *  Copyright © 2017 ShiVa Technologies SAS. All rights reserved.
 *
 */

// LUA bindings in C
#include "lua.hpp"

// OSX stuff in ObjC
#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif

// make things accessible from outside
#define EXPORT __attribute__((visibility("default")))


////////////////////////////////////////////////////////
// HELPERS
////////////////////////////////////////////////////////

void MacAlertFunction(const char* caption, const char* message) {
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"OK"];
    //[alert addButtonWithTitle:@"Cancel"];
    [alert setMessageText:[NSString stringWithUTF8String:message]];
    [alert setInformativeText:[NSString stringWithUTF8String:caption]];
    [alert setAlertStyle:NSWarningAlertStyle];
    
    if ([alert runModal] == NSAlertFirstButtonReturn) {
    }
    //[alert release];
}

/////////////////

/* Pop-up a Windows message box with your choice of message and caption */
int lua_msgbox(lua_State* L) {
    const char* message = luaL_checkstring(L, 1);
    const char* caption = luaL_optstring(L, 2, "ShiVa 2.0 Message");
    MacAlertFunction(message, caption);
    //int result = MessageBox(NULL, message, caption, MB_OK);
    //lua_pushnumber(L, result);
    return 1;
}


////////////////////////////////////////////////////////
// INIT
////////////////////////////////////////////////////////

EXPORT extern "C" int libinit (lua_State* L) {
    lua_register(L, "msgbox",  lua_msgbox);
    return 0;
}
