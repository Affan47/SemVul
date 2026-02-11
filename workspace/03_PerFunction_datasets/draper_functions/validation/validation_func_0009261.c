lua_setupvalue(lua_State *L, int idx, int n)
{
  cTValue *f = index2adr(L, idx);
  TValue *val;
  const char *name;
  api_checknelems(L, 1);
  name = lj_debug_uvnamev(f, (uint32_t)(n-1), &val);
  if (name) {
    L->top--;
    copyTV(L, val, L->top);
    lj_gc_barrier(L, funcV(f), L->top);
  }
  return name;
}
