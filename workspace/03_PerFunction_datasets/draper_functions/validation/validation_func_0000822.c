read_offset(LHALH1Decoder *decoder, unsigned int *result)
{
	unsigned int offset;
	int future, offset2;


	future = peek_bits(&decoder->bit_stream_reader, 8);

	if (future < 0) {
		return 0;
	}

	offset = decoder->offset_lookup[future];


	read_bits(&decoder->bit_stream_reader,
	          decoder->offset_lengths[offset]);

	offset2 = read_bits(&decoder->bit_stream_reader, 6);

	if (offset2 < 0) {
		return 0;
	}

	*result = (offset << 6) | (unsigned int) offset2;

	return 1;
}
