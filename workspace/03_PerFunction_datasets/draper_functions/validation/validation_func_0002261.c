Add3(char *p, unsigned short *crc, char *file)
{
	char *s;
	for(s=p;*s;s++)
		QCC_CRC_ProcessByte(crc, *s);
}
