str_upper (lua_State *L) {
  size_t l;
  size_t i;
  luaL_Buffer b;
  const char *s = luaL_check_lstr(L, 1, &l);
  luaL_buffinit(L, &b);
  for (i=0; i<l; i++)
    luaL_putchar(&b, toupper((unsigned char)(s[i])));
  luaL_pushresult(&b);
  return 1;
}
