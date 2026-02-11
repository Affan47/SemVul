set_min(struct RASTER_MAP_PTR *from, int col,
		    struct RASTER_MAP_PTR *to)
{
    if (from == NULL) {
	switch (to->type) {
	case CELL_TYPE:
	    *to->data.c = INT_MAX;
	    break;
	case FCELL_TYPE:
	    *to->data.f = FLT_MAX;
	    break;
	case DCELL_TYPE:
	    *to->data.d = DBL_MAX;
	    break;
	}
    }
    else {
	switch (to->type) {
	case CELL_TYPE:
	    *to->data.c = (*to->data.c < from->data.c[col]) ?
		*to->data.c : from->data.c[col];
	    break;
	case FCELL_TYPE:
	    *to->data.f = (*to->data.f < from->data.f[col]) ?
		*to->data.f : from->data.f[col];
	    break;
	case DCELL_TYPE:
	    *to->data.d = (*to->data.d < from->data.d[col]) ?
		*to->data.d : from->data.d[col];
	    break;
	}
    }
}
