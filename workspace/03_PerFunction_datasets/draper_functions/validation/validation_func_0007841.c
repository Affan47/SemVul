gayle_read (uaecptr addr)
{
	uaecptr oaddr = addr;
	uae_u32 v = 0;
	int got = 0;
#ifdef JIT
	special_mem |= S_READ;
#endif
	if (currprefs.cs_ide == IDE_A600A1200) {
		if ((addr & 0xA0000) != 0xA0000)
			return 0;
	}
	addr &= 0xffff;
	if (currprefs.cs_pcmcia) {
		if (currprefs.cs_ide != IDE_A600A1200) {
			if (addr == GAYLE_IRQ_1200) {
				v = read_gayle_irq ();
				got = 1;
			} else if (addr == GAYLE_INT_1200) {
				v = read_gayle_int ();
				got = 1;
			}
		}
		if (addr == GAYLE_CS_1200) {
			v = read_gayle_cs ();
			got = 1;
			if (PCMCIA_LOG)
				write_log (_T("PCMCIA STATUS READ %08X=%02X PC=%08X\n"), oaddr, (uae_u32)v & 0xff, M68K_GETPC);
		} else if (addr == GAYLE_CFG_1200) {
			v = read_gayle_cfg ();
			got = 1;
			if (PCMCIA_LOG)
				write_log (_T("PCMCIA CONFIG READ %08X=%02X PC=%08X\n"), oaddr, (uae_u32)v & 0xff, M68K_GETPC);
		}
	}
	if (!got)
		v = gayle_read2 (addr);
	if (GAYLE_LOG)
		write_log (_T("GAYLE_READ %08X=%02X PC=%08X\n"), oaddr, (uae_u32)v & 0xff, M68K_GETPC);
	return v;
}
