FLAC__bool FLAC__bitreader_read_raw_int32(FLAC__BitReader *br, FLAC__int32 *val, uint32_t bits)
{
	FLAC__uint32 uval, mask;

	if (bits < 1 || ! FLAC__bitreader_read_raw_uint32(br, &uval, bits))
		return false;


	mask = 1u << (bits - 1);
	*val = (uval ^ mask) - mask;
	return true;
}
