broadsheet_verify_spiflash(struct broadsheetfb_par *par,
						int *flash_type)
{
	int err = 0;
	u8 sig;

	err = broadsheet_spiflash_op_on_address(par, 0xAB, 0x00000000);
	if (err)
		goto failout;

	err = broadsheet_spiflash_read_byte(par, &sig);
	if (err)
		goto failout;

	if ((sig != 0x10) && (sig != 0x11)) {
		dev_err(par->info->device, "Unexpected flash type\n");
		err = -EINVAL;
		goto failout;
	}

	*flash_type = sig;

failout:
	broadsheet_write_reg(par, 0x0208, 0);
	return err;
}
