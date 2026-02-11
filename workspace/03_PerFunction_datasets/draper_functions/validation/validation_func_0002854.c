cat_open_gsc(struct catalog *cat)
{
	if (cat->name == NULL) {
		cat->name = catalogs[GSC_NAME];
		cat->ref_count = 0;
		cat->data = NULL;
	}
	cat->ref_count ++;

	cat->cat_search = gsc_search;
	cat->cat_get = NULL;
	cat->cat_add = NULL;
	cat->cat_sync = NULL;
	cat->flags = CAT_STAR_TYPE_SREF | CAT_ASTROMET;
	return cat;
}
