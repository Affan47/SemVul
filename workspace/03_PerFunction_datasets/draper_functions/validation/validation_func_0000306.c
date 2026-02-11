xen_hyper_get_uptime_hyper(void)
{
	ulong jiffies, tmp1, tmp2;
	ulonglong jiffies_64, wrapped;

	if (symbol_exists("jiffies_64")) {
		get_symbol_data("jiffies_64", sizeof(ulonglong), &jiffies_64);
		wrapped = (jiffies_64 & 0xffffffff00000000ULL);
		if (wrapped) {
			wrapped -= 0x100000000ULL;
			jiffies_64 &= 0x00000000ffffffffULL;
			jiffies_64 |= wrapped;
               		jiffies_64 += (ulonglong)(300*machdep->hz);
		} else {
			tmp1 = (ulong)(uint)(-300*machdep->hz);
			tmp2 = (ulong)jiffies_64;
			jiffies_64 = (ulonglong)(tmp2 - tmp1);
		}
	} else if (symbol_exists("jiffies")) {
		get_symbol_data("jiffies", sizeof(long), &jiffies);
		jiffies_64 = (ulonglong)jiffies;
	} else {
		jiffies_64 = 0;
	}

	return jiffies_64;
}
