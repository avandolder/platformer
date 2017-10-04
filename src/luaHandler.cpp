#include "common.hpp"

/* This file sets up lua and pushes all of the pf functions and constants
   you can access in it */

lua_State *pfLuaState;

int luaChangeObjectHealth(lua_State *L);
int luaGetCurrentObjectNumber(lua_State *L);
int luaMoveObject(lua_State *L);
int luaGetObjectPosition(lua_State *L);
int luaSetObjectPosition(lua_State *L);

int startLua()
{
    int error = 0;

    pfLuaState = luaL_newstate();

    luaL_openlibs(pfLuaState);

    lua_pushnumber(pfLuaState, -1);
    lua_setglobal(pfLuaState, "pfPlayer");

    lua_register(pfLuaState, "pfChangeObjectHealth", luaChangeObjectHealth);
    lua_register(pfLuaState, "pfGetCurrentObjectNumber", luaGetCurrentObjectNumber);
    lua_register(pfLuaState, "pfMoveObject", luaMoveObject);
    lua_register(pfLuaState, "pfGetObjectPosition", luaGetObjectPosition);
    lua_register(pfLuaState, "pfSetObjectPosition", luaSetObjectPosition);

    return error;
}

int luaChangeObjectHealth(lua_State *L)
{
    int obj = luaL_checknumber(L, 1);
    int howMuch = luaL_checknumber(L, 2);

    if(obj == -1)
        player.changeHealth(howMuch);
    else
        game.getActiveObject(obj)->changeHealth(howMuch);

    return 0;
}

int luaGetCurrentObjectNumber(lua_State *L)
{
    lua_pushnumber(L, game.getCurrentObject());
    return 1;
}

int luaMoveObject(lua_State *L)
{
    int obj = luaL_checknumber(L, 1);
    int x = luaL_checknumber(L, 2);
    int y = luaL_checknumber(L, 3);

    if(obj == -1)
        player.move(x, y);
    else
        game.getActiveObject(obj)->move(x, y);

    return 0;
}

int luaGetObjectPosition(lua_State *L)
{
    int obj = luaL_checknumber(L, 1);

    if(obj == -1)
    {
        lua_pushnumber(L, player.getX());
        lua_pushnumber(L, player.getY());
    }
    else
    {
        lua_pushnumber(L, game.getActiveObject(obj)->getX());
        lua_pushnumber(L, game.getActiveObject(obj)->getY());
    }

    return 2;
}

int luaSetObjectPosition(lua_State *L)
{
    int obj = luaL_checknumber(L, 1);
    int x = luaL_checknumber(L, 2);
    int y = luaL_checknumber(L, 3);

    if(obj == -1)
        player.setPosition(x, y);
    else
        game.getActiveObject(obj)->setPosition(x, y);

    return 0;
}
