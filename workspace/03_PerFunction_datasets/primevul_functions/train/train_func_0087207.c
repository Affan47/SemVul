GF_Err gf_isom_purge_samples(GF_ISOFile *the_file, u32 trackNumber, u32 nb_samples)
{
	GF_TrackBox *trak;
#ifndef	GPAC_DISABLE_ISOM_FRAGMENTS
	GF_Err e;
	GF_TrackExtendsBox *trex;
	GF_SampleTableBox *stbl;
#endif
	trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (!trak) return GF_BAD_PARAM;


#ifndef	GPAC_DISABLE_ISOM_FRAGMENTS
	trex = the_file->moov->mvex ? GetTrex(the_file->moov, gf_isom_get_track_id(the_file,trackNumber) ) : NULL;
	if (!trex) return GF_BAD_PARAM;


	e = stbl_UnpackOffsets(trak->Media->information->sampleTable);
	if (e) return e;
	e = stbl_unpackCTS(trak->Media->information->sampleTable);
	if (e) return e;

	stbl = trak->Media->information->sampleTable;
	if (!stbl->TimeToSample || !stbl->SampleSize || !stbl->SampleToChunk) return GF_ISOM_INVALID_FILE;


	stbl_RemoveDTS(stbl, 1, nb_samples, 0);
	stbl_RemoveCTS(stbl, 1, nb_samples);
	stbl_RemoveSize(stbl, 1, nb_samples);
	stbl_RemoveChunk(stbl, 1, nb_samples);
	stbl_RemoveRedundant(stbl, 1, nb_samples);


	while (nb_samples) {
		stbl_RemoveRAP(stbl, 1);
		stbl_RemoveShadow(stbl, 1);
		stbl_RemoveSubSample(stbl, 1);
		stbl_RemovePaddingBits(stbl, 1);
		stbl_RemoveSampleGroup(stbl, 1);
		nb_samples--;
	}
	return GF_OK;
#else
	return GF_NOT_SUPPORTED;
#endif
}
