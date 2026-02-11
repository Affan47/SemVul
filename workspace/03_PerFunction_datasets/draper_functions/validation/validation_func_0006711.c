G__check_for_auto_masking(void)
{
    struct Cell_head cellhd;


    if (G__.auto_mask < -1)
	return G__.auto_mask;


    G__.auto_mask = (G_find_cell("MASK", G_mapset()) != 0);

    if (G__.auto_mask <= 0)
	return 0;


    if (G_get_cellhd("MASK", G_mapset(), &cellhd) >= 0) {
	if (cellhd.zone != G_zone() || cellhd.proj != G_projection()) {
	    G__.auto_mask = 0;
	    return 0;
	}
    }

    G_unopen_cell(G__.mask_fd);
    G__.mask_fd = G__open_cell_old("MASK", G_mapset());
    if (G__.mask_fd < 0) {
	G__.auto_mask = 0;
	G_warning(_("Unable to open automatic MASK file"));
	return 0;
    }


    G__.auto_mask = 1;

    return 1;
}
