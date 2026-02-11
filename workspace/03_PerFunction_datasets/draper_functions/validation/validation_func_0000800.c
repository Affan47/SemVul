wnd_scan_pri()
{
	int cnt, i;
	byte *src, *dest;

	if (WX >= 160) return;
	i = 0;
	cnt = 160 - WX;
	dest = PRI + WX;
	src = lcd.vbank[1] + ((R_LCDC&0x40)?0x1C00:0x1800) + (WT<<5);

	if (!priused(src))
	{
		memset(dest, 0, cnt);
		return;
	}

	while (cnt >= 8)
	{
		memset(dest, src[i++]&128, 8);
		dest += 8;
		cnt -= 8;
	}
	memset(dest, src[i]&128, cnt);
}
