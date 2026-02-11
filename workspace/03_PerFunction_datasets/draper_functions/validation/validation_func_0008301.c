lua_newthread (lua_State *L) {
  lua_State *L1;
  lua_lock(L);
  luaC_checkGC(L);
  L1 = &luaC_newobj(L, LUA_TTHREAD, sizeof(LX), NULL, offsetof(LX, l))->th;
  setthvalue(L, L->top, L1);
  api_incr_top(L);
  preinit_state(L1, G(L));
  L1->hookmask = L->hookmask;
  L1->basehookcount = L->basehookcount;
  L1->hook = L->hook;
  resethookcount(L1);
  luai_userstatethread(L, L1);
  stack_init(L1, L);
  lua_unlock(L);
  return L1;
}
