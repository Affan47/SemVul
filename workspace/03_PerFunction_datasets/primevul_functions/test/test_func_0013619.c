void luaV_finishget (lua_State *L, const TValue *t, TValue *key, StkId val,
                      const TValue *slot) {
  int loop;
  const TValue *tm;
  for (loop = 0; loop < MAXTAGLOOP; loop++) {
    if (slot == NULL) {
      lua_assert(!ttistable(t));
      tm = luaT_gettmbyobj(L, t, TM_INDEX);
      if (l_unlikely(notm(tm)))
        luaG_typeerror(L, t, "index");

    }
    else {
      lua_assert(isempty(slot));
      tm = fasttm(L, hvalue(t)->metatable, TM_INDEX);
      if (tm == NULL) {
        setnilvalue(s2v(val));
        return;
      }

    }
    if (ttisfunction(tm)) {
      luaT_callTMres(L, tm, t, key, val);
      return;
    }
    t = tm;
    if (luaV_fastget(L, t, key, slot, luaH_get)) {
      setobj2s(L, val, slot);
      return;
    }

  }
  luaG_runerror(L, "'__index' chain too long; possible loop");
}
