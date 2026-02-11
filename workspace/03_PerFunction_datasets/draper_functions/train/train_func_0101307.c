dbmap_release(dbmap_t *dm)
{
	void *implementation;

	dbmap_check(dm);

	implementation = dbmap_implementation(dm);

	dm->type = DBMAP_MAXTYPE;
	dm->magic = 0;
	WFREE(dm);

	return implementation;
}
