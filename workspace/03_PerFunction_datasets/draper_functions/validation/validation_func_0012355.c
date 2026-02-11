OTS_arrow_to_us(state n,state s,state e,state w) {
	return (is_OTS(n) && is_south(n)) || (is_OTS(s) && is_north(s))
		|| (is_OTS(e) && is_west(e)) || (is_OTS(w) && is_east(w));
}
