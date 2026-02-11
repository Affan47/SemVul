remove_rooms(int lx, int ly, int hx, int hy)
{
    int i;
    struct mkroom *croom;

    for (i = nroom - 1; i >= 0; --i) {
	croom = &rooms[i];
	if (croom->hx < lx || croom->lx >= hx ||
	    croom->hy < ly || croom->ly >= hy) continue;

	if (croom->lx < lx || croom->hx >= hx ||
	    croom->ly < ly || croom->hy >= hy) {


	    if (!croom->irregular) impossible("regular room in joined map");
	} else {

	    remove_room((unsigned)i);
	}
    }
}
