gp_free_site(geosite * fp)
{
    geosite *gp;
    int found = 0;

    G_debug(5, "gp_free_site");

    if (Site_top) {
	if (fp == Site_top) {
	    if (Site_top->next) {

		found = 1;
		Site_top = fp->next;
	    }
	    else {
		gp_free_sitemem(fp);
		G_free(fp);
		Site_top = NULL;
	    }
	}
	else {
	    for (gp = Site_top; gp && !found; gp = gp->next) {

		if (gp->next) {
		    if (gp->next == fp) {
			found = 1;
			gp->next = fp->next;
		    }
		}
	    }
	}

	if (found) {
	    gp_free_sitemem(fp);
	    G_free(fp);
	    fp = NULL;
	}

	return (1);
    }

    return (-1);
}
