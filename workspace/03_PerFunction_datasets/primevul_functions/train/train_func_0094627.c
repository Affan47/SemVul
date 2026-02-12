u64 gf_bs_available(GF_BitStream *bs)
{
	s64 cur, end;


	if ( (bs->bsmode == GF_BITSTREAM_WRITE)
	        || (bs->bsmode == GF_BITSTREAM_WRITE_DYN)
	   )
		return (u64) -1;


	if (bs->bsmode == GF_BITSTREAM_READ) {
		if (bs->size < bs->position)
			return 0;
		else
			return (bs->size - bs->position);
	}

	if (bs->bsmode==GF_BITSTREAM_FILE_READ) {
		if (bs->position>bs->size) return 0;
		return (bs->size - bs->position);
	}
	if (bs->cache_write)
		bs_flush_write_cache(bs);

	cur = gf_ftell(bs->stream);
	end = gf_fsize(bs->stream);
	gf_fseek(bs->stream, cur, SEEK_SET);

	return (u64) (end - cur);
}
