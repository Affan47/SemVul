caml_thread_code (code_t code, asize_t len)
{
  code_t p;
  int l [STOP + 1];
  int i;

  for (i = 0; i <= STOP; i++) {
    l [i] = 0;
  }

  l[PUSHACC] = l[ACC] = l[POP] = l[ASSIGN] =
  l[PUSHENVACC] = l[ENVACC] = l[PUSH_RETADDR] = l[APPLY] =
  l[APPTERM1] = l[APPTERM2] = l[APPTERM3] = l[RETURN] =
  l[GRAB] = l[PUSHGETGLOBAL] = l[GETGLOBAL] = l[SETGLOBAL] =
  l[PUSHATOM] = l[ATOM] = l[MAKEBLOCK1] = l[MAKEBLOCK2] =
  l[MAKEBLOCK3] = l[MAKEFLOATBLOCK] = l[GETFIELD] =
  l[GETFLOATFIELD] = l[SETFIELD] = l[SETFLOATFIELD] =
  l[BRANCH] = l[BRANCHIF] = l[BRANCHIFNOT] = l[PUSHTRAP] =
  l[C_CALL1] = l[C_CALL2] = l[C_CALL3] = l[C_CALL4] = l[C_CALL5] =
  l[CONSTINT] = l[PUSHCONSTINT] = l[OFFSETINT] =
  l[OFFSETREF] = l[OFFSETCLOSURE] = l[PUSHOFFSETCLOSURE] = 1;


  l[APPTERM] = l[CLOSURE] = l[PUSHGETGLOBALFIELD] =
  l[GETGLOBALFIELD] = l[MAKEBLOCK] = l[C_CALLN] =
  l[BEQ] = l[BNEQ] = l[BLTINT] = l[BLEINT] = l[BGTINT] = l[BGEINT] =
  l[BULTINT] = l[BUGEINT] = l[GETPUBMET] = 2;
  len /= sizeof(opcode_t);
  for (p = code; p < code + len; ) {
    opcode_t instr = *p;
    if (instr < 0 || instr > STOP){


      instr = STOP;
    }
    *p++ = (opcode_t)(caml_instr_table[instr] - caml_instr_base);
    if (instr == SWITCH) {
      uint32 sizes = *p++;
      uint32 const_size = sizes & 0xFFFF;
      uint32 block_size = sizes >> 16;
      p += const_size + block_size;
    } else if (instr == CLOSUREREC) {
      uint32 nfuncs = *p++;
      p++;
      p += nfuncs;
    } else {
      p += l[instr];
    }
  }
  Assert(p == code + len);
}
