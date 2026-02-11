luaH_newkey (lua_State *L, Table *t, const TValue *key) {
  Node *mp;
  if (ttisnil(key)) luaG_runerror(L, "table index is nil");
  else if (ttisnumber(key) && luai_numisnan(L, nvalue(key)))
    luaG_runerror(L, "table index is NaN");
  mp = mainposition(t, key);
  if (!ttisnil(gval(mp)) || isdummy(mp)) {
    Node *othern;
    Node *n = getfreepos(t);
    if (n == NULL) {
      rehash(L, t, key);

      return luaH_set(L, t, key);
    }
    lua_assert(!isdummy(n));
    othern = mainposition(t, gkey(mp));
    if (othern != mp) {

      while (gnext(othern) != mp) othern = gnext(othern);
      gnext(othern) = n;
      *n = *mp;
      gnext(mp) = NULL;
      setnilvalue(gval(mp));
    }
    else {

      gnext(n) = gnext(mp);
      gnext(mp) = n;
      mp = n;
    }
  }
  setobj2t(L, gkey(mp), key);
  luaC_barrierback(L, obj2gco(t), key);
  lua_assert(ttisnil(gval(mp)));
  return gval(mp);
}
