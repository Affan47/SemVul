static s32 BS_CutBuffer(GF_BitStream *bs)
{
	s32 nbBytes;
	if ( (bs->bsmode != GF_BITSTREAM_WRITE_DYN) && (bs->bsmode != GF_BITSTREAM_WRITE)) return (u32) -1;

	gf_bs_align(bs);

	nbBytes = (u32) (bs->size - bs->position);
	if (!nbBytes || (nbBytes == 0xFFFFFFFF) || (bs->position >= 0xFFFFFFFF)) return 0;


	bs->size = bs->position;
	return nbBytes;
}
