rlc_a(void) 	 { UINT8 i=M_Cy; if (R.A & 0x80) SET(C_FLAG); else CLR(C_FLAG); R.A <<= 1; if (i) R.A |= 0x01; else R.A &= 0xfe; }
