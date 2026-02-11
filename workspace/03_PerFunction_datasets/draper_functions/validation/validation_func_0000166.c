cia_wget (uaecptr addr)
{
	int r = (addr & 0xf00) >> 8;
	uae_u16 v = 0xffff;

#ifdef JIT
	special_mem |= S_READ;
#endif

	if (!isgaylenocia (addr))
		return v;

	cia_wait_pre ();
	switch ((addr >> 12) & 3)
	{
	case 0:
		if (!issinglecia ())
			v = (ReadCIAB (r) << 8) | ReadCIAA (r);
		break;
	case 1:
		v = (ReadCIAB (r) << 8) | 0xff;
		break;
	case 2:
		v = (0xff << 8) | ReadCIAA (r);
		break;
	case 3:
		if (currprefs.cpu_model == 68000 && currprefs.cpu_compatible)
			v = regs.irc;
		if (warned > 0) {
			write_log (_T("cia_wget: unknown CIA address %x PC=%x\n"), addr, M68K_GETPC);
			warned--;
		}
		break;
	}
	cia_wait_post (v);
	return v;
}
