decrypt_C10707_cpu(int cpu, int region)
{
	int A;
	unsigned char *rom = memory_region(region);
	int diff = memory_region_length(region) / 2;

	memory_set_opcode_base(cpu,rom+diff);


	for (A = 0;A < 0x10000;A++)
		rom[A+diff] = swap_bits_5_6(rom[A]);
}
