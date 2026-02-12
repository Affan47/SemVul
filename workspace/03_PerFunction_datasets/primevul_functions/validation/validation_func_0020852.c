static unsigned int luai_makeseed (lua_State *L) {
  char buff[3 * sizeof(size_t)];
  unsigned int h = cast_uint(time(NULL));
  int p = 0;
  addbuff(buff, p, L);
  addbuff(buff, p, &h);
  addbuff(buff, p, &lua_newstate);
  lua_assert(p == sizeof(buff));
  return luaS_hash(buff, p, h, 1);
}
