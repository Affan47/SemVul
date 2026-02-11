isosurf_set_mask_mode(int id, Tcl_Interp * interp, int argc, char *argv[])
{
    int mode, isosurf_id;

    if (argc != 5) {
	Tcl_SetResult(interp,
		      "Usage: <map_obj> isosurf set_mask_mode isosurf_id [0 | 1]",
		      TCL_VOLATILE);
	return (TCL_ERROR);
    }

    isosurf_id = atoi(argv[3]);

    if (Tcl_GetBoolean(interp, argv[4], &mode) != TCL_OK) {
	Tcl_SetResult(interp, "Error: must be BOOLEAN", TCL_VOLATILE);
	return (TCL_ERROR);
    }
    else {
	GVL_isosurf_set_maskmode(id, isosurf_id, mode);
    }

    return (TCL_OK);
}
