u64 gf_isom_get_duration(GF_ISOFile *movie)
{
	if (!movie || !movie->moov || !movie->moov->mvhd) return 0;


#ifndef GPAC_DISABLE_ISOM_WRITE
	gf_isom_update_duration(movie);
#endif

	return movie->moov->mvhd->duration;
}
