GF_Err gf_isom_use_compact_size(GF_ISOFile *movie, u32 trackNumber, Bool CompactionOn)
{
	GF_TrackBox *trak;
	u32 i, size;
	GF_SampleSizeBox *stsz;
	GF_Err e;

	e = CanAccessMovie(movie, GF_ISOM_OPEN_WRITE);
	if (e) return e;

	trak = gf_isom_get_track_from_file(movie, trackNumber);
	if (!trak) return GF_BAD_PARAM;

	if (!trak->Media || !trak->Media->information
	        || !trak->Media->information->sampleTable || !trak->Media->information->sampleTable->SampleSize)
		return GF_ISOM_INVALID_FILE;

	stsz = trak->Media->information->sampleTable->SampleSize;


	if (!CompactionOn) {
		if (stsz->type == GF_ISOM_BOX_TYPE_STSZ) return GF_OK;
		stsz->type = GF_ISOM_BOX_TYPE_STSZ;

		stsz->sampleSize = 0;
		if (!stsz->sampleCount) return GF_OK;

		if (!stsz->sizes) return GF_OK;
		size = stsz->sizes[0];

		for (i=1; i<stsz->sampleCount; i++) {
			if (size != stsz->sizes[i]) {
				size = 0;
				break;
			}
		}
		if (size) {
			gf_free(stsz->sizes);
			stsz->sizes = NULL;
			stsz->sampleSize = size;
		}
		return GF_OK;
	}


	if (stsz->type == GF_ISOM_BOX_TYPE_STZ2) return GF_OK;


	if (stsz->sampleSize) {

		if (stsz->sizes) gf_free(stsz->sizes);
		stsz->sizes = (u32*) gf_malloc(sizeof(u32)*stsz->sampleCount);
		if (!stsz->sizes) return GF_OUT_OF_MEM;
		memset(stsz->sizes, stsz->sampleSize, sizeof(u32));
	}

	stsz->sampleSize = 0;
	stsz->type = GF_ISOM_BOX_TYPE_STZ2;
	return GF_OK;
}
