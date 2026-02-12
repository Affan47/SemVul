static FLAC__bool bitreader_read_from_client_(FLAC__BitReader *br)
{
	uint32_t start, end;
	size_t bytes;
	FLAC__byte *target;


	if(br->consumed_words > 0) {
		crc16_update_block_(br);

		start = br->consumed_words;
		end = br->words + (br->bytes? 1:0);
		memmove(br->buffer, br->buffer+start, FLAC__BYTES_PER_WORD * (end - start));

		br->words -= start;
		br->consumed_words = 0;
	}


	bytes = (br->capacity - br->words) * FLAC__BYTES_PER_WORD - br->bytes;
	if(bytes == 0)
		return false;
	target = ((FLAC__byte*)(br->buffer+br->words)) + br->bytes;


#if WORDS_BIGENDIAN
#else
	if(br->bytes)
		br->buffer[br->words] = SWAP_BE_WORD_TO_HOST(br->buffer[br->words]);
#endif


	if(!br->read_callback(target, &bytes, br->client_data))
		return false;


#if WORDS_BIGENDIAN
#else
	end = (br->words*FLAC__BYTES_PER_WORD + br->bytes + (uint32_t)bytes + (FLAC__BYTES_PER_WORD-1)) / FLAC__BYTES_PER_WORD;
	for(start = br->words; start < end; start++)
		br->buffer[start] = SWAP_BE_WORD_TO_HOST(br->buffer[start]);
#endif


	end = br->words*FLAC__BYTES_PER_WORD + br->bytes + (uint32_t)bytes;
	br->words = end / FLAC__BYTES_PER_WORD;
	br->bytes = end % FLAC__BYTES_PER_WORD;

	return true;
}
