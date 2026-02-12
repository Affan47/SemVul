void gf_bs_write_int(GF_BitStream *bs, s32 _value, s32 nBits)
{
	u32 value, nb_shift;
	s32 max_shift = sizeof(s32) * 8;
	if (!nBits) return;
	nBits = bs_handle_nbits_overflow(bs, nBits, max_shift);


	value = (u32) _value;
	nb_shift = max_shift - nBits;
	if (nb_shift)
		value <<= nb_shift;

	while (--nBits >= 0) {

		BS_WriteBit (bs, ((s32)value) < 0);
		value <<= 1;
	}
}
