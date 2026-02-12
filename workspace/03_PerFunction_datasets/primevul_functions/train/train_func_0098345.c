void lua_push_int_table_entry(lua_State *L, const char *key, u_int64_t value) {
  if(L) {
    lua_pushstring(L, key);


    lua_pushnumber(L, (lua_Number)value);
    lua_settable(L, -3);
  }
}
