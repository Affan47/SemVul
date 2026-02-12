while(1) {
		while(br->consumed_words < br->words) {
			brword b = br->buffer[br->consumed_words] << br->consumed_bits;
			if(b) {
				i = COUNT_ZERO_MSBS(b);
				*val += i;
				i++;
				br->consumed_bits += i;
				if(br->consumed_bits >= FLAC__BITS_PER_WORD) {
					br->consumed_words++;
					br->consumed_bits = 0;
				}
				return true;
			}
			else {
				*val += FLAC__BITS_PER_WORD - br->consumed_bits;
				br->consumed_words++;
				br->consumed_bits = 0;

			}
		}


		if(br->bytes*8 > br->consumed_bits) {
			const uint32_t end = br->bytes * 8;
			brword b = (br->buffer[br->consumed_words] & (FLAC__WORD_ALL_ONES << (FLAC__BITS_PER_WORD-end))) << br->consumed_bits;
			if(b) {
				i = COUNT_ZERO_MSBS(b);
				*val += i;
				i++;
				br->consumed_bits += i;
				FLAC__ASSERT(br->consumed_bits < FLAC__BITS_PER_WORD);
				return true;
			}
			else {
				*val += end - br->consumed_bits;
				br->consumed_bits = end;
				FLAC__ASSERT(br->consumed_bits < FLAC__BITS_PER_WORD);

			}
		}
		if(!bitreader_read_from_client_(br))
			return false;
	}
