static const char *varinfo (lua_State *L, const TValue *o) {
  CallInfo *ci = L->ci;
  const char *name = NULL;
  const char *kind = NULL;
  if (isLua(ci)) {
    kind = getupvalname(ci, o, &name);
    if (!kind && isinstack(ci, o))
      kind = getobjname(ci_func(ci)->p, currentpc(ci),
                        cast_int(cast(StkId, o) - (ci->func + 1)), &name);
  }
  return formatvarinfo(L, kind, name);
}
