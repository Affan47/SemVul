void luaV_finishset (lua_State *L, const TValue *t, TValue *key,
                     TValue *val, const TValue *slot) {
  int loop;
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    const TValue *tm;
    if (slot != NULL) {
      Table *h = hvalue(t);
      lua_assert(isempty(slot));
      tm = fasttm(L, h->metatable, TM_NEWINDEX);
      if (tm == NULL) {
        luaH_finishset(L, h, key, slot, val);
        invalidateTMcache(h);
        luaC_barrierback(L, obj2gco(h), val);
        return;
      }

    }
    else {
      tm = luaT_gettmbyobj(L, t, TM_NEWINDEX);
      if (l_unlikely(notm(tm)))
        luaG_typeerror(L, t, "index");
    }

    if (ttisfunction(tm)) {
      luaT_callTM(L, tm, t, key, val);
      return;
    }
    t = tm;
    if (luaV_fastget(L, t, key, slot, luaH_get)) {
      luaV_finishfastset(L, t, slot, val);
      return;
    }

  }
  luaG_runerror(L, "'__newindex' chain too long; possible loop");
}
