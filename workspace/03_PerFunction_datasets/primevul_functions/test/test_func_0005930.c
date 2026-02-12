static u64 naludmx_next_start_code(GF_BitStream *bs, u64 offset, u64 fsize, u32 *sc_size)
{
	u32 pos=0, nb_zeros=0;
	while (offset+pos<fsize) {
		u8 b = gf_bs_read_u8(bs);
		pos++;
		switch (b) {
		case 1:

			if (nb_zeros>=2) {
				*sc_size = (nb_zeros==2) ? 3 : 4;
				return offset+pos;
			}
			nb_zeros = 0;
			break;
		case 0:
			nb_zeros++;
			break;
		default:
			nb_zeros=0;
			break;
		}
	}

	return 0;
}
