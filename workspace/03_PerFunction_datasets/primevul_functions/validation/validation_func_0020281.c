FLAC__bool FLAC__bitreader_read_rice_signed(FLAC__BitReader *br, int *val, uint32_t parameter)
{
	FLAC__uint32 lsbs = 0, msbs = 0;
	uint32_t uval;

	FLAC__ASSERT(0 != br);
	FLAC__ASSERT(0 != br->buffer);
	FLAC__ASSERT(parameter <= 31);


	if(!FLAC__bitreader_read_unary_unsigned(br, &msbs))
		return false;


	if(!FLAC__bitreader_read_raw_uint32(br, &lsbs, parameter))
		return false;


	uval = (msbs << parameter) | lsbs;
	if(uval & 1)
		*val = -((int)(uval >> 1)) - 1;
	else
		*val = (int)(uval >> 1);

	return true;
}
