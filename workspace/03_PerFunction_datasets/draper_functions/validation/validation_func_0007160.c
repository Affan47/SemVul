header_remove_bits (unsigned short bit, char *vals)
{
	register unsigned char *inptr = (unsigned char *) vals;

	while (*inptr != '\0')
		gmime_special_table[*inptr++] &= ~bit;
}
