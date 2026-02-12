u32 gf_bs_peek_bits(GF_BitStream *bs, u32 numBits, u64 byte_offset)
{
	u64 curPos;
	u32 curBits, ret, current, nb_zeros;

	if ( (bs->bsmode != GF_BITSTREAM_READ) && (bs->bsmode != GF_BITSTREAM_FILE_READ)) return 0;
	if (!numBits || (bs->size < bs->position + byte_offset)) return 0;


	curPos = bs->position;
	curBits = bs->nbBits;
	current = bs->current;
	nb_zeros = bs->nb_zeros;

	if (byte_offset) {
		if (bs->remove_emul_prevention_byte) {
			while (byte_offset) {
				gf_bs_read_int(bs, 8);
				byte_offset--;
			}
		} else {
			gf_bs_seek(bs, bs->position + byte_offset);
		}
	}
	ret = gf_bs_read_int(bs, numBits);


	gf_bs_seek(bs, curPos);

	bs->nbBits = curBits;
	bs->current = current;
	bs->nb_zeros = nb_zeros;
	return ret;
}
