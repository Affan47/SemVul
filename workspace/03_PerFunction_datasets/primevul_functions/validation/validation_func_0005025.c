GF_Err gf_isom_add_desc_to_root_od(GF_ISOFile *movie, const GF_Descriptor *theDesc)
{
	GF_Err e;
	GF_Descriptor *desc, *dupDesc;

	e = CanAccessMovie(movie, GF_ISOM_OPEN_WRITE);
	if (e) return e;
	e = gf_isom_insert_moov(movie);
	if (e) return e;

	if (!movie->moov->iods) {
		e = AddMovieIOD(movie->moov, 0);
		if (e) return e;
	}
	if (theDesc->tag==GF_ODF_IPMP_TL_TAG) gf_isom_set_root_iod(movie);

	desc = movie->moov->iods->descriptor;


	switch (desc->tag) {
	case GF_ODF_ISOM_IOD_TAG:
	case GF_ODF_ISOM_OD_TAG:

		e = gf_odf_desc_copy((GF_Descriptor *)theDesc, &dupDesc);
		if (e) return e;

		movie->LastError = gf_odf_desc_add_desc(desc, dupDesc);
		if (movie->LastError) gf_odf_desc_del((GF_Descriptor *)dupDesc);
		break;
	default:
		movie->LastError = GF_ISOM_INVALID_FILE;
		break;
	}
	return movie->LastError;
}
