ath5k_hw_ini_registers(struct ath5k_hw *ah, unsigned int size,
		const struct ath5k_ini *ini_regs, int change_channel)
{
	unsigned int i;


	for (i = 0; i < size; i++) {


		if (change_channel &&
				ini_regs[i].ini_register >= AR5K_PCU_MIN &&
				ini_regs[i].ini_register <= AR5K_PCU_MAX)
			continue;

		switch (ini_regs[i].ini_mode) {
		case AR5K_INI_READ:

			ath5k_hw_reg_read(ah, ini_regs[i].ini_register);
			break;
		case AR5K_INI_WRITE:
		default:
			AR5K_REG_WAIT(i);
			ath5k_hw_reg_write(ah, ini_regs[i].ini_value,
					ini_regs[i].ini_register);
		}
	}
}
