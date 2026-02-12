GF_Err gf_isom_set_final_name(GF_ISOFile *movie, char *filename)
{
	GF_Err e;
	if (!movie ) return GF_BAD_PARAM;


	e = CanAccessMovie(movie, GF_ISOM_OPEN_EDIT);
	if (e) return e;

	if (filename) {

		if ( (movie->openMode == GF_ISOM_OPEN_EDIT)
		        && movie->fileName && !strcmp(filename, movie->fileName))
			return GF_BAD_PARAM;
		if (movie->finalName) gf_free(movie->finalName);
		movie->finalName = gf_strdup(filename);
		if (!movie->finalName) return GF_OUT_OF_MEM;
		gf_isom_disable_inplace_rewrite(movie);
	}
	return GF_OK;
}
