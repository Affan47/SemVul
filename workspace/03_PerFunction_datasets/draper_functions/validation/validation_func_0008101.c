vdp_data_r(void)
{
	int read = 0;


	vdp_cmdpart = 0;


	switch (vdp_code & 0x0f)
	{
		case 0x00:
			read = VDP_VRAM_WORD(vdp_address & ~1);
			break;

		case 0x04:
			read = VDP_VSRAM_WORD(vdp_address & ~1);
			break;

		default:
			logerror("%06x: VDP illegal read type %02x\n", activecpu_get_previouspc(), vdp_code);
			read = 0x00;
			break;
	}


	vdp_address += segac2_vdp_regs[15];
	return read;
}
