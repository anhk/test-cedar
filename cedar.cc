


#include "cedarpp.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

static int cedar_new(lua_State *L)
{
    int n = lua_gettop(L);
    if (n > 0) {
        return luaL_error(L, "no need arguments here.");
    }

    cedar::da <int> **trie = (cedar::da <int>**)
        lua_newuserdata(L, sizeof(void**));
    if (trie == NULL) {
        return luaL_error(L, "no enough memory here.");
    }
    *trie = new cedar::da<int>;
    if (*trie == NULL) {
        lua_pop(L, 1);
        return luaL_error(L, "no enough memory here.");
    }
    return 1;
}

static int cedar_update(lua_State *L)
{
    int n = lua_gettop(L);
    if (n < 2) {
        return luaL_error(L, "no enough arguments.");
    }

    cedar::da <int> **trie = (cedar::da <int>**)
        lua_touserdata(L, 1);
    if (trie == NULL || *trie == NULL) {
        return luaL_error(L, "bad argument. <1>");
    }

    const char *key = luaL_checkstring(L, 2);
    if (key == NULL) {
        return luaL_error(L, "bad argument. <2>");
    }

    int value = lua_tonumber(L, 3);
    (*trie)->update(key) = value;

    lua_pushboolean(L, 1);
    return 1;
}

static int cedar_match(lua_State *L)
{
    int n = lua_gettop(L);
    if (n < 2) {
        return luaL_error(L, "no enough arguments.");
    }

    cedar::da <int> **trie = (cedar::da <int>**)
        lua_touserdata(L, 1);

    const char *key = luaL_checkstring(L, 2);
    if (key == NULL) {
        return luaL_error(L, "bad argument. <2>");
    }

    cedar::da<int>::result_pair_type result_pair[BUFSIZ];
    size_t ret = (*trie)->commonPrefixSearch (key, result_pair, BUFSIZ);

    if (ret <= 0) {
        lua_pushnil(L);
        return 1;
    }

    if (ret == 1) {
        int value = result_pair[0].value;
        lua_pushnumber(L, value);
        return 1;
    }

    lua_createtable(L, ret, 0);
    for (int i = 0; i < ret; i ++) {
        lua_pushnumber(L, i+1);
        lua_pushnumber(L, result_pair[i].value);
        lua_settable(L, -3);
    }

    return 1;
}

static int cedar_erase(lua_State *L)
{
    int n = lua_gettop(L);
    if (n < 2) {
        return luaL_error(L, "no enough arguments.");
    }

    cedar::da <int> **trie = (cedar::da <int>**)
        lua_touserdata(L, 1);

    const char *key = luaL_checkstring(L, 2);
    if (key == NULL) {
        return luaL_error(L, "bad argument. <2>");
    }

    int ret = (*trie)->erase(key);

    if (ret == 0) {
        lua_pushboolean(L, 1);
    } else {
        lua_pushboolean(L, 0);
    }
    return 1;
}


static const struct luaL_Reg cedar_reg [] = {
    {"new", cedar_new},
    {"update", cedar_update},
    {"match", cedar_match},
    {"erase", cedar_erase},
    {NULL, NULL}
};


extern "C" int luaopen_cedar(lua_State *L)
{
    luaL_openlib(L, "microsoft_hmac", cedar_reg, 0);
    return 1;
}


