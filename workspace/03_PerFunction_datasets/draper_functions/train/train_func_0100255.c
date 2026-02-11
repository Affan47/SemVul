show_grid()
{
    SHOW_ALL_NL;

    if (! some_grid_selected()) {
	fputs("\tgrid is OFF\n", stderr);
	return;
    }


    fprintf(stderr, "\t%s grid drawn at",
	    (polar_grid_angle != 0) ? "Polar" : "Rectangular");
#define SHOW_GRID(axis)						\
    if (axis_array[axis].gridmajor)				\
	fprintf(stderr, " %s", axis_defaults[axis].name);	\
    if (axis_array[axis].gridminor)				\
	fprintf(stderr, " m%s", axis_defaults[axis].name);
    SHOW_GRID(FIRST_X_AXIS );
    SHOW_GRID(FIRST_Y_AXIS );
    SHOW_GRID(SECOND_X_AXIS);
    SHOW_GRID(SECOND_Y_AXIS);
    SHOW_GRID(FIRST_Z_AXIS );
    SHOW_GRID(COLOR_AXIS);
    SHOW_GRID(POLAR_AXIS);
#undef SHOW_GRID
    fputs(" tics\n", stderr);


    fprintf(stderr, "\tMajor grid drawn with");
    save_linetype(stderr, &(grid_lp), FALSE);
    fprintf(stderr, "\n\tMinor grid drawn with");
    save_linetype(stderr, &(mgrid_lp), FALSE);
    fputc('\n', stderr);
    if (polar_grid_angle)
	fprintf(stderr, "\tGrid radii drawn every %f %s\n",
		polar_grid_angle / ang2rad,
		(ang2rad == 1.0) ? "radians" : "degrees");

    fprintf(stderr, "\tGrid drawn at %s\n", (grid_layer==-1) ? "default layer" : ((grid_layer==0) ? "back" : "front"));
}
