GP_delete_site(int id)
{
    int i, j, found = 0;

    G_debug(3, "GP_delete_site(): id=%d", id);

    if (GP_site_exists(id)) {
	gp_delete_site(id);

	for (i = 0; i < Next_site && !found; i++) {
	    if (Site_ID[i] == id) {
		found = 1;
		for (j = i; j < Next_site; j++) {
		    Site_ID[j] = Site_ID[j + 1];
		}
	    }
	}

	if (found) {
	    --Next_site;
	    return (1);
	}
    }

    return (-1);
}
