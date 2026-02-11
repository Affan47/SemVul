wantdoor(x, y, distance)
int x, y;
genericptr_t distance;
{
    int ndist;

    if (*(int*)distance > (ndist = distu(x, y))) {
	gx = x;
	gy = y;
	*(int*)distance = ndist;
    }
}
