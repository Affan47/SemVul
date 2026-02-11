getfuncname (lua_State *L, CallInfo *ci, const char **name) {
  Instruction i;
  if ((isLua(ci) && ci->tailcalls > 0) || !isLua(ci - 1))
    return NULL;
  ci--;
  i = ci_func(ci)->l.p->code[currentpc(L, ci)];
  if (GET_OPCODE(i) == OP_CALL || GET_OPCODE(i) == OP_TAILCALL ||
      GET_OPCODE(i) == OP_TFORLOOP)
    return getobjname(L, ci, GETARG_A(i), name);
  else
    return NULL;
}
