ClosedSplineToPolygon (float* cpx, float* cpy, int cpcount){
    register int cpi;

    if (cpcount < 3) {
        _x = cpx;
	_y = cpy;
	_count = cpcount;
    } else {
        mlcount = 0;
        CalcSection(
	    cpx[cpcount - 1], cpy[cpcount - 1], cpx[0], cpy[0],
	    cpx[1], cpy[1], cpx[2], cpy[2]
        );

        for (cpi = 1; cpi < cpcount - 2; ++cpi) {
	    CalcSection(
	        cpx[cpi - 1], cpy[cpi - 1], cpx[cpi], cpy[cpi],
	        cpx[cpi + 1], cpy[cpi + 1], cpx[cpi + 2], cpy[cpi + 2]
            );
        }

        CalcSection(
	    cpx[cpi - 1], cpy[cpi - 1], cpx[cpi], cpy[cpi],
	    cpx[cpi + 1], cpy[cpi + 1], cpx[0], cpy[0]
        );
        CalcSection(
	    cpx[cpi], cpy[cpi], cpx[cpi + 1], cpy[cpi + 1],
	    cpx[0], cpy[0], cpx[1], cpy[1]
        );
        _x = mlx;
        _y = mly;
        _count = mlcount;
    }
}
