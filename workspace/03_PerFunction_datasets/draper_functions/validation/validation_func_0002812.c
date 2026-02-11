getesc(str, len)
unsigned char *str;
int len;
{
	register int	c;


	while (len > 0) {
		c = *str;
		if (c < 0x20 || 0x2f < c)
			break;
		len--, str++;
	}

	if (--len < 0 || (c = *str++) < 0x30 || 0x7e < c)
		return (unsigned char *)NULL;

	return str;
}
