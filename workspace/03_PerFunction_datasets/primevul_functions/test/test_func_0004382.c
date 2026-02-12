GF_ISOFile *gf_isom_create_movie(const char *fileName, GF_ISOOpenMode OpenMode, const char *tmp_dir)
{
	GF_Err e;

	GF_ISOFile *mov = gf_isom_new_movie();
	if (!mov) return NULL;
	mov->openMode = OpenMode;


	mov->movieFileMap = NULL;


	if (OpenMode == GF_ISOM_OPEN_WRITE) {
		const char *ext;


		mov->fileName = fileName ? gf_strdup(fileName) : NULL;
		e = gf_isom_datamap_new(fileName, NULL, GF_ISOM_DATA_MAP_WRITE, &mov->editFileMap);
		if (e) goto err_exit;


		ext = gf_file_ext_start(fileName);
		if (ext && (!strnicmp(ext, ".mov", 4) || !strnicmp(ext, ".qt", 3))) {
			gf_isom_set_brand_info((GF_ISOFile *) mov, GF_ISOM_BRAND_QT, 512);
		} else {
			gf_isom_set_brand_info((GF_ISOFile *) mov, GF_ISOM_BRAND_ISOM, 1);
		}
	} else {

		mov->finalName = fileName ? gf_strdup(fileName) : NULL;
		e = gf_isom_datamap_new("_gpac_isobmff_tmp_edit", tmp_dir, GF_ISOM_DATA_MAP_WRITE, &mov->editFileMap);
		if (e) {
			gf_isom_set_last_error(NULL, e);
			gf_isom_delete_movie(mov);
			return NULL;
		}

		gf_isom_set_brand_info( (GF_ISOFile *) mov, GF_ISOM_BRAND_ISOM, 1);
	}


	mov->mdat = (GF_MediaDataBox *) gf_isom_box_new(GF_ISOM_BOX_TYPE_MDAT);
	if (!mov->mdat) {
		gf_isom_set_last_error(NULL, GF_OUT_OF_MEM);
		gf_isom_delete_movie(mov);
		return NULL;
	}
	gf_list_add(mov->TopBoxes, mov->mdat);


	mov->storageMode = GF_ISOM_STORE_FLAT;
	return mov;

err_exit:
	gf_isom_set_last_error(NULL, e);
	if (mov) gf_isom_delete_movie(mov);
	return NULL;
}
