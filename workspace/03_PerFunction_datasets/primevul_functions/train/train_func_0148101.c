static CallInfo *findpcall (lua_State *L) {
  CallInfo *ci;
  for (ci = L->ci; ci != NULL; ci = ci->previous) {
    if (ci->callstatus & CIST_YPCALL)
      return ci;
  }
  return NULL;
}
