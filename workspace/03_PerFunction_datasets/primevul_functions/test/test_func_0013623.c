static int forlimit (lua_State *L, lua_Integer init, const TValue *lim,
                                   lua_Integer *p, lua_Integer step) {
  if (!luaV_tointeger(lim, p, (step < 0 ? F2Iceil : F2Ifloor))) {

    lua_Number flim;
    if (!tonumber(lim, &flim))
      luaG_forerror(L, lim, "limit");

    if (luai_numlt(0, flim)) {
      if (step < 0) return 1;
      *p = LUA_MAXINTEGER;
    }
    else {
      if (step > 0) return 1;
      *p = LUA_MININTEGER;
    }
  }
  return (step > 0 ? init > *p : init < *p);
}
