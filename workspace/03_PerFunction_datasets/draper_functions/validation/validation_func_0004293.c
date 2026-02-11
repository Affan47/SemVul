Nviz_new_fringe(nv_data *data,
				    int id, unsigned long color,
				    double elev, int nw, int ne, int sw, int se)
{
    int num;
    int *surf;
    struct fringe_data *f;

    if (!GS_surf_exists(id)) {

	surf = GS_get_surf_list(&num);
	if (num < 1)
	    return NULL;
	id = surf[0];
	G_free(surf);
    }


    f = (struct fringe_data *) G_malloc(sizeof(struct fringe_data));
    f->id = id;
    f->color = color;
    f->elev = elev;
    f->where[0] = nw;
    f->where[1] = ne;
    f->where[2] = sw;
    f->where[3] = se;

    data->fringe = (struct fringe_data **) G_realloc(data->fringe, data->num_fringes + 1 * sizeof(struct fringe_data *));
    data->fringe[data->num_fringes++] = f;

    return f;
}
