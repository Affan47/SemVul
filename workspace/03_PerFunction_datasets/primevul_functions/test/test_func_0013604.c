void luaV_finishOp (lua_State *L) {
  CallInfo *ci = L->ci;
  StkId base = ci->func + 1;
  Instruction inst = *(ci->u.l.savedpc - 1);
  OpCode op = GET_OPCODE(inst);
  switch (op) {
    case OP_MMBIN: case OP_MMBINI: case OP_MMBINK: {
      setobjs2s(L, base + GETARG_A(*(ci->u.l.savedpc - 2)), --L->top);
      break;
    }
    case OP_UNM: case OP_BNOT: case OP_LEN:
    case OP_GETTABUP: case OP_GETTABLE: case OP_GETI:
    case OP_GETFIELD: case OP_SELF: {
      setobjs2s(L, base + GETARG_A(inst), --L->top);
      break;
    }
    case OP_LT: case OP_LE:
    case OP_LTI: case OP_LEI:
    case OP_GTI: case OP_GEI:
    case OP_EQ: {
      int res = !l_isfalse(s2v(L->top - 1));
      L->top--;
#if defined(LUA_COMPAT_LT_LE)
      if (ci->callstatus & CIST_LEQ) {
        ci->callstatus ^= CIST_LEQ;
        res = !res;
      }
#endif
      lua_assert(GET_OPCODE(*ci->u.l.savedpc) == OP_JMP);
      if (res != GETARG_k(inst))
        ci->u.l.savedpc++;
      break;
    }
    case OP_CONCAT: {
      StkId top = L->top - 1;
      int a = GETARG_A(inst);
      int total = cast_int(top - 1 - (base + a));
      setobjs2s(L, top - 2, top);
      L->top = top - 1;
      luaV_concat(L, total);
      break;
    }
    case OP_CLOSE: {
      ci->u.l.savedpc--;
      break;
    }
    case OP_RETURN: {
      StkId ra = base + GETARG_A(inst);


      L->top = ra + ci->u2.nres;

      ci->u.l.savedpc--;
      break;
    }
    default: {

      lua_assert(op == OP_TFORCALL || op == OP_CALL ||
           op == OP_TAILCALL || op == OP_SETTABUP || op == OP_SETTABLE ||
           op == OP_SETI || op == OP_SETFIELD);
      break;
    }
  }
}
