get_fp_ad (uae_u32 opcode, uae_u32 * ad)
{
	uae_u16 tmp;
	uaecptr tmppc;
	int mode;
	int reg;

	mode = (opcode >> 3) & 7;
	reg = opcode & 7;
	switch (mode) {
		case 0:
		case 1:
			return 0;
		case 2:
			*ad = m68k_areg (regs, reg);
			break;
		case 3:
			*ad = m68k_areg (regs, reg);
			break;
		case 4:
			*ad = m68k_areg (regs, reg);
			break;
		case 5:
			*ad = m68k_areg (regs, reg) + (uae_s32) (uae_s16) x_next_iword ();
			break;
		case 6:
			*ad = x_get_disp_ea_020 (m68k_areg (regs, reg), x_next_iword ());
			break;
		case 7:
			switch (reg) {
		case 0:
			*ad = (uae_s32) (uae_s16) x_next_iword ();
			break;
		case 1:
			*ad = x_next_ilong ();
			break;
		case 2:
			*ad = m68k_getpc ();
			*ad += (uae_s32) (uae_s16) x_next_iword ();
			break;
		case 3:
			tmppc = m68k_getpc ();
			tmp = x_next_iword ();
			*ad = x_get_disp_ea_020 (tmppc, tmp);
			break;
		default:
			return 0;
			}
	}
	return 1;
}
