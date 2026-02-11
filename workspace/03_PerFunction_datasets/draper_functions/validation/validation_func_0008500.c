traceexec (lua_State *L, StkId base, StkId top, lua_Hook linehook) {
  CallInfo *ci = infovalue(base-1);
  int *lineinfo = ci->func->f.l->lineinfo;
  int pc = (*ci->pc - ci->func->f.l->code) - 1;
  int newline;
  if (pc == 0) {
    ci->line = 1;
    ci->refi = 0;
    ci->lastpc = pc+1;
  }
  newline = luaG_getline(lineinfo, pc, ci->line, &ci->refi);

  if (newline != ci->line || pc <= ci->lastpc) {
    ci->line = newline;
    L->top = top;
    luaD_lineHook(L, base-1, newline, linehook);
  }
  ci->lastpc = pc;
}
