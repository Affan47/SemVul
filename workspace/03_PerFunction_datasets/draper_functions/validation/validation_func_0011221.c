PSLLD_PqIb(bxInstruction_c *i)
{
#if BX_SUPPORT_MMX
  BX_CPU_THIS_PTR prepareMMX();
  BX_CPU_THIS_PTR prepareFPU2MMX();

  BxPackedMmxRegister op = BX_READ_MMX_REG(i->rm());
  Bit8u shift = i->Ib();

  if(shift > 31) MMXUQ(op) = 0;
  else
  {
    MMXUD0(op) <<= shift;
    MMXUD1(op) <<= shift;
  }


  BX_WRITE_MMX_REG(i->rm(), op);
#else
  BX_INFO(("PSLLD_PqIb: required MMX, use --enable-mmx option"));
  exception(BX_UD_EXCEPTION, 0, 0);
#endif
}
