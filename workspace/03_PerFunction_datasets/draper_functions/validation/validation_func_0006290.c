point_assign(struct line_pnts *Points, int index, int with_z,
			 POINT * res)
{
    res->x = Points->x[index];
    res->y = Points->y[index];
    if (with_z) {
	res->z = Points->z[index];
    }
    else {
	res->z = 0;
    }
    return;
}
