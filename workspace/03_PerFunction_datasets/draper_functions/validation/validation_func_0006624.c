N_write_array_3d_to_rast3d(N_array_3d * array, char *name, int mask)
{
    void *map = NULL;
    int changemask = 0;
    int x, y, z, cols, rows, depths, count, type;
    double d1 = 0.0, f1 = 0.0;
    N_array_3d *data = array;
    G3D_Region region;


    G3d_getWindow(&region);


    cols = region.cols;
    rows = region.rows;
    depths = region.depths;
    type = data->type;


    if (data->cols != cols)
	G_fatal_error
	    ("N_write_array_3d_to_rast3d: the data array size is different from the current region settings");
    if (data->rows != rows)
	G_fatal_error
	    ("N_write_array_3d_to_rast3d: the data array size is different from the current region settings");
    if (data->depths != depths)
	G_fatal_error
	    ("N_write_array_3d_to_rast3d: the data array size is different from the current region settings");


    if (type == DCELL_TYPE)
	map =
	    G3d_openCellNew(name, DCELL_TYPE, G3D_USE_CACHE_DEFAULT, &region);
    else if (type == FCELL_TYPE)
	map =
	    G3d_openCellNew(name, FCELL_TYPE, G3D_USE_CACHE_DEFAULT, &region);

    if (map == NULL)
	G3d_fatalError(_("Error opening g3d map <%s>"), name);

    G_message(_("Write 3d array to g3d map <%s>"), name);


    if (mask) {
	if (G3d_maskFileExists()) {
	    changemask = 0;
	    if (G3d_maskIsOff(map)) {
		G3d_maskOn(map);
		changemask = 1;
	    }
	}
    }

    count = 0;
    for (z = 0; z < depths; z++) {
	G_percent(z, depths - 1, 10);
	for (y = 0; y < rows; y++) {
	    for (x = 0; x < cols; x++) {
		if (type == FCELL_TYPE) {
		    f1 = N_get_array_3d_f_value(data, x, y, z);
		    G3d_putFloat(map, x, y, z, f1);
		}
		else if (type == DCELL_TYPE) {
		    d1 = N_get_array_3d_d_value(data, x, y, z);
		    G3d_putDouble(map, x, y, z, d1);
		}
	    }
	}
    }


    if (mask) {
	if (G3d_maskFileExists())
	    if (G3d_maskIsOn(map) && changemask)
		G3d_maskOff(map);
    }


    if (!G3d_closeCell(map))
	G3d_fatalError(map, NULL, 0, _("Error closing g3d file"));

    return;
}
