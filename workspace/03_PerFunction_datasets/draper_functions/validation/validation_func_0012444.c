msp430_get_op_mode_single (short insn)
{
  struct msp430_op_mode m;
  int s_reg;
  int d_reg;

  alu.saved_sr = sr;


  m.as = (insn >> 4) & 3;
  m.byte = (insn >> 6) & 1;
  m.rd = m.rs = d_reg = s_reg = insn & 0xf;

  switch (m.as)
    {
    case 0:

      cg2 = 0;
      m.ms = REGISTER;
      break;

    case 1:


      if (s_reg == 2)
	m.ms = ABSOLUTE;
      else if (s_reg == 0)
	m.ms = SYMBOLIC;
      else if (s_reg == 3)
	m.ms = REGISTER;
      else
	m.ms = INDEXED;

      cg2 = 1;
      break;

    case 2:
      m.ms = INDERECT;
      if (s_reg == 2 || s_reg == 3)
	m.ms = REGISTER;
      cg1 = 4;
      cg2 = 2;
      break;

    case 3:
      if (s_reg == 0)
	m.ms = IMMEDIATE;
      else
	m.ms = INDERECTINC;
      if (s_reg == 2 || s_reg == 3)
	m.ms = REGISTER;
      cg1 = 8;
      cg2 = -1;
      break;
    }

  return m;
}
