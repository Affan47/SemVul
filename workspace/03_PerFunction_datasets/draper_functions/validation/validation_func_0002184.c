gsd_fringe_vert_line(float bot, geosurf * surf, int col, int side)
{
    int row;
    int cnt;
    float pt[4];
    typbuff *buff;
    long offset;
    int ycnt;

    GS_set_draw(GSD_FRONT);
    gsd_pushmatrix();
    gsd_do_scale(1);
    gsd_translate(surf->x_trans, surf->y_trans, surf->z_trans);


    buff = gs_get_att_typbuff(surf, ATT_TOPO, 0);
    ycnt = VROWS(surf);
    gsd_bgnline();

    row = 0;

    pt[X] = col * (surf->x_mod * surf->xres);
    pt[Y] =
	((surf->rows - 1) * surf->yres) - (row * (surf->y_mod * surf->yres));
    pt[Z] = bot;
    gsd_vert_func(pt);

    offset = (row * surf->y_mod * surf->cols) + (col * surf->x_mod);
    GET_MAPATT(buff, offset, pt[Z]);
    pt[Z] = pt[Z] * surf->z_exag;
    gsd_vert_func(pt);

    cnt = 1;
    for (row = 0; row < ycnt - 1; row++) {

	pt[X] = col * (surf->x_mod * surf->xres);
	pt[Y] =
	    ((surf->rows - 1) * surf->yres) -
	    (row * (surf->y_mod * surf->yres));
	offset = (row * surf->y_mod * surf->cols) + (col * surf->x_mod);
	GET_MAPATT(buff, offset, pt[Z]);
	pt[Z] = pt[Z] * surf->z_exag;
	gsd_vert_func(pt);
	cnt++;
    }

    row--;
    pt[X] = col * (surf->x_mod * surf->xres);
    pt[Y] =
	((surf->rows - 1) * surf->yres) - (row * (surf->y_mod * surf->yres));
    pt[Z] = bot;
    gsd_vert_func(pt);

    row = 0;
    pt[X] = col * (surf->x_mod * surf->xres);
    pt[Y] =
	((surf->rows - 1) * surf->yres) - (row * (surf->y_mod * surf->yres));
    pt[Z] = bot;
    gsd_vert_func(pt);

    gsd_endline();

    GS_done_draw();
    gsd_popmatrix();
    gsd_flush();

    return;
}
