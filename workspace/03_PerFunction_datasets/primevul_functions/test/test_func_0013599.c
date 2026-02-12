static const char *funcnamefromcall (lua_State *L, CallInfo *ci,
                                                   const char **name) {
  if (ci->callstatus & CIST_HOOKED) {
    *name = "?";
    return "hook";
  }
  else if (ci->callstatus & CIST_FIN) {
    *name = "__gc";
    return "metamethod";
  }
  else if (isLua(ci))
    return funcnamefromcode(L, ci_func(ci)->p, currentpc(ci), name);
  else
    return NULL;
}
