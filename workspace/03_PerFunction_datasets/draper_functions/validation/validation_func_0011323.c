zoran_show(struct seq_file *p, void *v)
{
	struct zoran *zr = p->private;
	int i;

	seq_printf(p, "ZR36067 registers:\n");
	for (i = 0; i < 0x130; i += 16)
		seq_printf(p, "%03X %08X  %08X  %08X  %08X \n", i,
			   btread(i), btread(i+4), btread(i+8), btread(i+12));
	return 0;
}
