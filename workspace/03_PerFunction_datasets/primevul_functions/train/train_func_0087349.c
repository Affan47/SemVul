GF_Err gf_isom_open_segment(GF_ISOFile *movie, const char *fileName, u64 start_range, u64 end_range, GF_ISOSegOpenMode flags)
{
#ifdef	GPAC_DISABLE_ISOM_FRAGMENTS
	return GF_NOT_SUPPORTED;
#else
	u64 MissingBytes;
	GF_Err e;
	u32 i;
	Bool segment_map_assigned = GF_FALSE;
	Bool is_scalable_segment = (flags & GF_ISOM_SEGMENT_SCALABLE_FLAG) ? GF_TRUE : GF_FALSE;
	Bool no_order_check = (flags & GF_ISOM_SEGMENT_NO_ORDER_FLAG) ? GF_TRUE: GF_FALSE;
	GF_DataMap *tmp = NULL;
	GF_DataMap *orig_file_map = NULL;
	if (!movie || !movie->moov || !movie->moov->mvex) return GF_BAD_PARAM;
	if (movie->openMode != GF_ISOM_OPEN_READ) return GF_BAD_PARAM;


	if (is_scalable_segment) {
		tmp = NULL;
		e = gf_isom_datamap_new(fileName, NULL, GF_ISOM_DATA_MAP_READ_ONLY, &tmp);
		if (e) return e;

		orig_file_map = movie->movieFileMap;
		movie->movieFileMap = tmp;
	} else {
		if (movie->movieFileMap)
			gf_isom_release_segment(movie, GF_FALSE);

		e = gf_isom_datamap_new(fileName, NULL, GF_ISOM_DATA_MAP_READ_ONLY, &movie->movieFileMap);
		if (e) return e;
	}
	movie->moov->compressed_diff = 0;
	movie->current_top_box_start = 0;

	if (start_range || end_range) {
		if (end_range > start_range) {
			gf_bs_seek(movie->movieFileMap->bs, end_range+1);
			gf_bs_truncate(movie->movieFileMap->bs);
		}
		gf_bs_seek(movie->movieFileMap->bs, start_range);
		movie->current_top_box_start = start_range;
	}

	for (i=0; i<gf_list_count(movie->moov->trackList); i++) {
		GF_TrackBox *trak = (GF_TrackBox*)gf_list_get(movie->moov->trackList, i);

		if (!is_scalable_segment) {

			if (trak->Media->information->dataHandler == NULL) {
				trak->Media->information->dataHandler = movie->movieFileMap;
			}
		} else {
			trak->present_in_scalable_segment = GF_FALSE;
		}
	}
	if (no_order_check) movie->NextMoofNumber = 0;


	e = gf_isom_parse_movie_boxes(movie, NULL, &MissingBytes, GF_TRUE);

	if (!is_scalable_segment)
		return e;

	for (i=0; i<gf_list_count(movie->moov->trackList); i++) {
		GF_TrackBox *trak = (GF_TrackBox*)gf_list_get(movie->moov->trackList, i);
		if (trak->present_in_scalable_segment) {


			trak->Media->information->scalableDataHandler = tmp;
			if (!segment_map_assigned) {
				trak->Media->information->scalableDataHandler = tmp;
				segment_map_assigned = GF_TRUE;
			}

			trak->Media->information->dataHandler = tmp;
		}
	}
	movie->movieFileMap = 	orig_file_map;
	return e;
#endif
}
