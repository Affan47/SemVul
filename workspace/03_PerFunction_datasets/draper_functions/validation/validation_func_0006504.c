luaL_checkudata(lua_State *L, int idx, const char *tname)
{
  cTValue *o = index2adr(L, idx);
  if (tvisudata(o)) {
    GCudata *ud = udataV(o);
    cTValue *tv = lj_tab_getstr(tabV(registry(L)), lj_str_newz(L, tname));
    if (tv && tvistab(tv) && tabV(tv) == tabref(ud->metatable))
      return uddata(ud);
  }
  lj_err_argtype(L, idx, tname);
  return NULL;
}
