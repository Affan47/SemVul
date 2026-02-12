ptp_unpack_EOS_ImageFormat (PTPParams* params, unsigned char** data )
{


	const unsigned char* d = *data;
	uint32_t n = dtoh32a( d );
	uint32_t l, s1, c1, s2 = 0, c2 = 0;

	if (n != 1 && n !=2) {
		ptp_debug (params, "parsing EOS ImageFormat property failed (n != 1 && n != 2: %d)", n);
		return 0;
	}

	l = dtoh32a( d+=4 );
	if (l != 0x10) {
		ptp_debug (params, "parsing EOS ImageFormat property failed (l != 0x10: 0x%x)", l);
		return 0;
	}

	d+=4;
	s1 = dtoh32a( d+=4 );
	c1 = dtoh32a( d+=4 );

	if (n == 2) {
		l = dtoh32a( d+=4 );
		if (l != 0x10) {
			ptp_debug (params, "parsing EOS ImageFormat property failed (l != 0x10: 0x%x)", l);
			return 0;
		}
		d+=4;
		s2 = dtoh32a( d+=4 );
		c2 = dtoh32a( d+=4 );
	}

	*data = (unsigned char*) d+4;


	if( s1 >= 0xe )
		s1--;
	if( s2 >= 0xe )
		s2--;

	return ((s1 & 0xF) << 12) | ((c1 & 0xF) << 8) | ((s2 & 0xF) << 4) | ((c2 & 0xF) << 0);
}
