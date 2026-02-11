do_move(char *buf)
{
    double east, north;

    if (!scan_en(buf, &east, &north, 1)) {
	bad_line(buf);
	return -1;
    }

    cur_east = east;
    cur_north = north;

    return (0);
}
