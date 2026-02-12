static void collectvalidlines (lua_State *L, Closure *f) {
  if (noLuaClosure(f)) {
    setnilvalue(s2v(L->top));
    api_incr_top(L);
  }
  else {
    int i;
    TValue v;
    const Proto *p = f->l.p;
    int currentline = p->linedefined;
    Table *t = luaH_new(L);
    sethvalue2s(L, L->top, t);
    api_incr_top(L);
    setbtvalue(&v);
    if (!p->is_vararg)
      i = 0;
    else {
      lua_assert(GET_OPCODE(p->code[0]) == OP_VARARGPREP);
      currentline = nextline(p, currentline, 0);
      i = 1;
    }
    for (; i < p->sizelineinfo; i++) {
      currentline = nextline(p, currentline, i);
      luaH_setint(L, t, currentline, &v);
    }
  }
}
