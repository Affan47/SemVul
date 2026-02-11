snd_emu10k1_efx_suspend(struct snd_emu10k1 *emu)
{
	int i, len;

	len = emu->audigy ? 0x200 : 0x100;
	for (i = 0; i < len; i++)
		emu->saved_gpr[i] = snd_emu10k1_ptr_read(emu, emu->gpr_base + i, 0);

	len = emu->audigy ? 0x100 : 0xa0;
	for (i = 0; i < len; i++) {
		emu->tram_val_saved[i] = snd_emu10k1_ptr_read(emu, TANKMEMDATAREGBASE + i, 0);
		emu->tram_addr_saved[i] = snd_emu10k1_ptr_read(emu, TANKMEMADDRREGBASE + i, 0);
		if (emu->audigy) {
			emu->tram_addr_saved[i] >>= 12;
			emu->tram_addr_saved[i] |=
				snd_emu10k1_ptr_read(emu, A_TANKMEMCTLREGBASE + i, 0) << 20;
		}
	}

	len = emu->audigy ? 2 * 1024 : 2 * 512;
	for (i = 0; i < len; i++)
		emu->saved_icode[i] = snd_emu10k1_efx_read(emu, i);
}
