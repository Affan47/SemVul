check_line( Line *ball_line, int type, int anchor, int range_start, int range_end, Coord *pt ) {
	Line line;
	if ( type == LINE_HORI )
		line_set_hori( &line, anchor );
	else
		line_set_vert( &line, anchor );
	line_intersect( &line, ball_line, pt );
	if ( type == LINE_HORI ) {
		if ( pt->x >= range_start && pt->x <= range_end ) return 1;
		return 0;
	}
	else {
		if ( pt->y >= range_start && pt->y <= range_end ) return 1;
		return 0;
	}
}
