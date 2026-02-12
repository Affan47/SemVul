GF_Err FlushCaptureMode(GF_ISOFile *movie)
{
	GF_Err e;
	if (movie->openMode != GF_ISOM_OPEN_WRITE) {
		if (!movie->editFileMap) return GF_ISOM_INVALID_MODE;
		return GF_OK;
	}

	if (gf_bs_get_position(movie->editFileMap->bs)) return GF_OK;

	if (!strcmp(movie->fileName, "_gpac_isobmff_redirect")) {
		if (!movie->on_block_out) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[ISOBMFF] Missing output block callback, cannot write\n"));
			return GF_BAD_PARAM;
		}

		gf_bs_del(movie->editFileMap->bs);
		movie->editFileMap->bs = gf_bs_new_cbk(movie->on_block_out, movie->on_block_out_usr_data, movie->on_block_out_block_size);
	}


	if (movie->brand) {
		e = gf_isom_box_size((GF_Box *)movie->brand);
		if (e) return e;
		e = gf_isom_box_write((GF_Box *)movie->brand, movie->editFileMap->bs);
		if (e) return e;
	}
	if (movie->pdin) {
		e = gf_isom_box_size((GF_Box *)movie->pdin);
		if (e) return e;
		e = gf_isom_box_write((GF_Box *)movie->pdin, movie->editFileMap->bs);
		if (e) return e;
	}
	movie->mdat->bsOffset = gf_bs_get_position(movie->editFileMap->bs);


	gf_bs_write_long_int(movie->editFileMap->bs, 0, 64);
	gf_bs_write_long_int(movie->editFileMap->bs, 0, 64);
	return GF_OK;
}
