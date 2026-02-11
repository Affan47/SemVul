RETnear32_Iw(bxInstruction_c *i)
{
  BX_ASSERT(BX_CPU_THIS_PTR cpu_mode != BX_MODE_LONG_64);

#if BX_DEBUGGER
  BX_CPU_THIS_PTR show_flag |= Flag_ret;
#endif

  RSP_SPECULATIVE;

  Bit16u imm16 = i->Iw();
  Bit32u return_EIP = pop_32();
  if (return_EIP > BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled)
  {
    BX_ERROR(("RETnear32_Iw: offset outside of CS limits"));
    exception(BX_GP_EXCEPTION, 0, 0);
  }
  EIP = return_EIP;

  if (BX_CPU_THIS_PTR sregs[BX_SEG_REG_SS].cache.u.segment.d_b)
    ESP += imm16;
  else
     SP += imm16;

  RSP_COMMIT;

  BX_INSTR_UCNEAR_BRANCH(BX_CPU_ID, BX_INSTR_IS_RET, EIP);
}
