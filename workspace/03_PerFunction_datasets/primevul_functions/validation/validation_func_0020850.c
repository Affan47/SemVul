void luaE_warnerror (lua_State *L, const char *where) {
  TValue *errobj = s2v(L->top - 1);
  const char *msg = (ttisstring(errobj))
                  ? svalue(errobj)
                  : "error object is not a string";

  luaE_warning(L, "error in ", 1);
  luaE_warning(L, where, 1);
  luaE_warning(L, " (", 1);
  luaE_warning(L, msg, 1);
  luaE_warning(L, ")", 0);
}
