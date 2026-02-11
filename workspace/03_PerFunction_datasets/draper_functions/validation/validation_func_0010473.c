sym_getfreq (struct sym_hcb *np)
{
	u_int f1, f2;
	int gen = 8;

	getfreq (np, gen);
	f1 = getfreq (np, gen);
	f2 = getfreq (np, gen);
	if (f1 > f2) f1 = f2;
	return f1;
}
