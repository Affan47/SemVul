read_eeprom(void __iomem *ioaddr, int location, int addr_len)
{
	int i;
	unsigned retval = 0;
	int read_cmd = location | (EE_READ_CMD << addr_len);

	RTL_W8 (Cfg9346, EE_ENB & ~EE_CS);
	RTL_W8 (Cfg9346, EE_ENB);
	eeprom_delay ();


	for (i = 4 + addr_len; i >= 0; i--) {
		int dataval = (read_cmd & (1 << i)) ? EE_DATA_WRITE : 0;
		RTL_W8 (Cfg9346, EE_ENB | dataval);
		eeprom_delay ();
		RTL_W8 (Cfg9346, EE_ENB | dataval | EE_SHIFT_CLK);
		eeprom_delay ();
	}
	RTL_W8 (Cfg9346, EE_ENB);
	eeprom_delay ();

	for (i = 16; i > 0; i--) {
		RTL_W8 (Cfg9346, EE_ENB | EE_SHIFT_CLK);
		eeprom_delay ();
		retval =
		    (retval << 1) | ((RTL_R8 (Cfg9346) & EE_DATA_READ) ? 1 :
				     0);
		RTL_W8 (Cfg9346, EE_ENB);
		eeprom_delay ();
	}


	RTL_W8(Cfg9346, 0);
	eeprom_delay ();

	return retval;
}
