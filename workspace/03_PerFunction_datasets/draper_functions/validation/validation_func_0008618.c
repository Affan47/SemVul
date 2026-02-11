gar_tdb_load_img(struct gar *gar, char *file, int basemap, int data,
		double north, double east, double south, double west)
{
	char path[4096];
	int rc;

	if (!gar)
		return 0;
	if (!gar->tdbdir) {
		log(1, "Trying to load [%s] but not TDB header seen yet\n", file);
		return -1;
	}
	sprintf(path, "%s/%s.img", gar->tdbdir, file);
	rc =  gar_img_load_dskimg(gar, path, basemap, data,
				DEGGAR(north), DEGGAR(east),
				DEGGAR(south), DEGGAR(west));
	if (rc < 0)
		log(1, "Failed to load [%s]\n", path);
	return rc;
}
