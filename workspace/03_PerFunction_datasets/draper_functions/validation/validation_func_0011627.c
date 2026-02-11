RETfar32_Iw(bxInstruction_c *i)
{
  invalidate_prefetch_q();

#if BX_DEBUGGER
  BX_CPU_THIS_PTR show_flag |= Flag_ret;
#endif

  Bit16u imm16 = i->Iw();
  Bit16u cs_raw;
  Bit32u eip;

  RSP_SPECULATIVE;

  if (protected_mode()) {
    return_protected(i, imm16);
    goto done;
  }

  eip    =          pop_32();
  cs_raw = (Bit16u) pop_32();


  if (eip > BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled) {
    BX_ERROR(("RETfar32_Iw: instruction pointer not within code segment limits"));
    exception(BX_GP_EXCEPTION, 0, 0);
  }

  load_seg_reg(&BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS], cs_raw);
  EIP = eip;

  if (BX_CPU_THIS_PTR sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    ESP += imm16;
  else
     SP += imm16;

done:
  RSP_COMMIT;

  BX_INSTR_FAR_BRANCH(BX_CPU_ID, BX_INSTR_IS_RET,
                      BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].selector.value, EIP);
}
