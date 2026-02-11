get_g3d_raster_value_as_double(void *map, int x, int y, int z,
				      int type, double nullval)
{
    double val = 0;
    float fvalue;
    double dvalue;

    if (type == FCELL_TYPE) {
	G3d_getValue(map, x, y, z, &fvalue, type);
	if (G3d_isNullValueNum(&fvalue, FCELL_TYPE))
	    val = nullval;
	else
	    val = (double)fvalue;
    }
    else {
	G3d_getValue(map, x, y, z, &dvalue, type);
	if (G3d_isNullValueNum(&dvalue, DCELL_TYPE))
	    val = nullval;
	else
	    val = dvalue;
    }

    return val;
}
