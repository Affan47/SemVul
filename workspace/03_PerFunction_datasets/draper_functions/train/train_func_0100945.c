radeon_pm_program_mode_reg(struct radeonfb_info *rinfo, u16 value,
				       u8 delay_required)
{
	u32 mem_sdram_mode;

	mem_sdram_mode  = INREG( MEM_SDRAM_MODE_REG);

	mem_sdram_mode &= ~MEM_SDRAM_MODE_REG__MEM_MODE_REG_MASK;
	mem_sdram_mode |= (value<<MEM_SDRAM_MODE_REG__MEM_MODE_REG__SHIFT)
		| MEM_SDRAM_MODE_REG__MEM_CFG_TYPE;
	OUTREG( MEM_SDRAM_MODE_REG, mem_sdram_mode);
	if (delay_required >= 2)
		mdelay(1);

	mem_sdram_mode |=  MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET;
	OUTREG( MEM_SDRAM_MODE_REG, mem_sdram_mode);
	if (delay_required >= 2)
		mdelay(1);

	mem_sdram_mode &= ~MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET;
	OUTREG( MEM_SDRAM_MODE_REG, mem_sdram_mode);
	if (delay_required >= 2)
		mdelay(1);

	if (delay_required) {
		do {
			if (delay_required >= 2)
				mdelay(1);
		} while ((INREG(MC_STATUS)
			  & (MC_STATUS__MEM_PWRUP_COMPL_A |
			     MC_STATUS__MEM_PWRUP_COMPL_B)) == 0);
	}
}
