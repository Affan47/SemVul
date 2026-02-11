cojag_sound_init(void)
{
	int i;


	for (i = 0; i < 0x80; i++)
	{

		jaguar_wave_rom[0x000 + i] = ((i <= 0x40) ? i : 0x80 - i) * 32767 / 0x40;


		jaguar_wave_rom[0x080 + i] = (int)(32767. * sin(2.0 * 3.1415927 * (double)i / (double)0x80));


		jaguar_wave_rom[0x100 + i] = (int)(32767. * sin(2.0 * 3.1415927 * (double)i / (double)0x80));


		jaguar_wave_rom[0x180 + i] = (int)(32767. * sin(2.0 * 3.1415927 * (double)i / (double)0x80));


		jaguar_wave_rom[0x200 + i] = (int)(32767. * sin(2.0 * 3.1415927 * (double)i / (double)0x80));


		jaguar_wave_rom[0x280 + i] = jaguar_wave_rom[0x000 + i] * (rand() % 32768) / 32768;


		jaguar_wave_rom[0x300 + i] = (i == 0x40) ? 32767 : 0;


		jaguar_wave_rom[0x380 + i] = rand() % 32768;
	}

#if ENABLE_SPEEDUP_HACKS
	install_mem_write32_handler(2, 0xf1a100, 0xf1a103, dsp_flags_w);
#endif
}
