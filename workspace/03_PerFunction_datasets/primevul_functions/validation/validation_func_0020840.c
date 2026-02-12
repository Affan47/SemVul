LUA_API void lua_close (lua_State *L) {
  lua_lock(L);
  L = G(L)->mainthread;
  close_state(L);
}
