sound_cpu_decrypt(void)
{
	data8_t *RAM = memory_region(REGION_CPU2);
	int i;


	RAM = memory_region(REGION_CPU2);
	for (i=0xc000; i<0x10000; i++)
		RAM[i+0x10000]=((RAM[i] & 0x20) << 1) | ((RAM[i] & 0x40) >> 1) | (RAM[i] & 0x9f);

	memory_set_opcode_base(1,RAM+0x10000);
}
