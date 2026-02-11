pushfilename (lua_State *L, const char *name)
{
  const char *path;
  const char *filename;
  luaQ_getfield(L, LUA_GLOBALSINDEX, "package");
  luaQ_getfield(L, -1, "cpath");
  lua_remove(L, -2);
  if (! (path = lua_tostring(L, -1)))
    luaL_error(L, LUA_QL("package.cpath") " must be a string");
  lua_pushliteral(L, "");
  while ((path = pushnexttemplate(L, path))) {
    filename = luaL_gsub(L, lua_tostring(L, -1), "?", name);
    lua_remove(L, -2);
    if (readable(filename))
      {
        lua_remove(L, -3);
        lua_remove(L, -2);
        return lua_tostring(L, -1);
      }
    lua_pushfstring(L, "\n\tno file " LUA_QS, filename);
    lua_remove(L, -2);
    lua_concat(L, 2);
  }
  lua_pushfstring(L, "module" LUA_QS "not found", name);
  lua_replace(L, -3);
  lua_concat(L, 2);
  lua_error(L);
  return 0;
}
