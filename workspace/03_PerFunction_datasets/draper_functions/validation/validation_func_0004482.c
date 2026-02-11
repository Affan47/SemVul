pdacf_transfer_stereo24le(u8 *dst, u32 xor, unsigned int size, unsigned long rdp_port)
{
	register u16 val1, val2, val3;
	register u32 xval1, xval2;

	while (size-- > 0) {
		val1 = inw(rdp_port);
		val2 = inw(rdp_port);
		val3 = inw(rdp_port);
		xval1 = ((((u32)val2 & 0xff) << 24) | ((u32)val1 << 8)) ^ xor;
		xval2 = (((u32)val3 << 16) | (val2 & 0xff00)) ^ xor;
		*dst++ = (u8)(xval1 >> 8);
		*dst++ = (u8)(xval1 >> 16);
		*dst++ = (u8)(xval1 >> 24);
		*dst++ = (u8)(xval2 >> 8);
		*dst++ = (u8)(xval2 >> 16);
		*dst++ = (u8)(xval2 >> 24);
	}
}
