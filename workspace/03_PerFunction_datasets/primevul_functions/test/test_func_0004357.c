GF_ISOFile *gf_isom_open_file(const char *fileName, GF_ISOOpenMode OpenMode, const char *tmp_dir)
{
	GF_Err e;
	u64 bytes;
	GF_ISOFile *mov = gf_isom_new_movie();
	if (!mov || !fileName) return NULL;

	mov->fileName = gf_strdup(fileName);
	mov->openMode = OpenMode;

#ifndef	GPAC_DISABLE_ISOM_FRAGMENTS
	if (OpenMode==GF_ISOM_OPEN_READ_DUMP)
		mov->store_traf_map = GF_TRUE;
#endif

	if ( (OpenMode == GF_ISOM_OPEN_READ) || (OpenMode == GF_ISOM_OPEN_READ_DUMP) || (OpenMode == GF_ISOM_OPEN_READ_EDIT) ) {
		if (OpenMode == GF_ISOM_OPEN_READ_EDIT) {
			mov->openMode = GF_ISOM_OPEN_READ_EDIT;


			e = gf_isom_datamap_new(NULL, tmp_dir, GF_ISOM_DATA_MAP_WRITE, & mov->editFileMap);
			if (e) {
				gf_isom_set_last_error(NULL, e);
				gf_isom_delete_movie(mov);
				return NULL;
			}
		} else {
			mov->openMode = GF_ISOM_OPEN_READ;
		}
		mov->es_id_default_sync = -1;


		e = gf_isom_datamap_new(fileName, NULL, GF_ISOM_DATA_MAP_READ_ONLY, &mov->movieFileMap);
		if (e) {
			gf_isom_set_last_error(NULL, e);
			gf_isom_delete_movie(mov);
			return NULL;
		}

		if (OpenMode == GF_ISOM_OPEN_READ_DUMP) {
			mov->FragmentsFlags |= GF_ISOM_FRAG_READ_DEBUG;
		}
	} else {

#ifdef GPAC_DISABLE_ISOM_WRITE

		gf_isom_delete_movie(mov);
		gf_isom_set_last_error(NULL, GF_ISOM_INVALID_MODE);
		return NULL;

#else


		mov->finalName = (char*)gf_malloc(strlen(fileName) + 5);
		if (!mov->finalName) {
			gf_isom_set_last_error(NULL, GF_OUT_OF_MEM);
			gf_isom_delete_movie(mov);
			return NULL;
		}
		strcpy(mov->finalName, "out_");
		strcat(mov->finalName, fileName);


		e = gf_isom_datamap_new(fileName, NULL, GF_ISOM_DATA_MAP_EDIT, &mov->movieFileMap);

		if (e) {
			gf_isom_set_last_error(NULL, e);
			gf_isom_delete_movie(mov);
			return NULL;
		}

		e = gf_isom_datamap_new("_gpac_isobmff_tmp_edit", tmp_dir, GF_ISOM_DATA_MAP_WRITE, & mov->editFileMap);
		if (e) {
			gf_isom_set_last_error(NULL, e);
			gf_isom_delete_movie(mov);
			return NULL;
		}

		mov->es_id_default_sync = -1;

#endif
	}


	mov->LastError = gf_isom_parse_movie_boxes(mov, NULL, &bytes, 0);

#if 0
	if (!mov->LastError && (OpenMode == GF_ISOM_OPEN_CAT_FRAGMENTS)) {
		gf_isom_datamap_del(mov->movieFileMap);

		mov->LastError = gf_isom_datamap_new(fileName, tmp_dir, GF_ISOM_DATA_MAP_CAT, & mov->movieFileMap);
	}
#endif

	if (mov->LastError) {
		gf_isom_set_last_error(NULL, mov->LastError);
		gf_isom_delete_movie(mov);
		return NULL;
	}

	mov->nb_box_init_seg = gf_list_count(mov->TopBoxes);
	return mov;
}
