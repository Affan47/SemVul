void luaE_shrinkCI (lua_State *L) {
  CallInfo *ci = L->ci->next;
  CallInfo *next;
  if (ci == NULL)
    return;
  L->nCcalls += L->nci;
  while ((next = ci->next) != NULL) {
    CallInfo *next2 = next->next;
    ci->next = next2;
    L->nci--;
    luaM_free(L, next);
    if (next2 == NULL)
      break;
    else {
      next2->previous = ci;
      ci = next2;
    }
  }
  L->nCcalls -= L->nci;
}
