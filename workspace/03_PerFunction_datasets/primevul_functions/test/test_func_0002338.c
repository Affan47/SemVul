static Bool ttml_check_range(TTMLInterval *interval, s64 ts_begin, s64 ts_end)
{

	if ((ts_begin != -1) && (ts_end != -1) && ((ts_begin>=interval->begin) && (ts_end<=interval->end))
	) {
		return GF_TRUE;
	}

	else if ((ts_begin==-1) && (ts_end != -1) && (ts_end<=interval->end)) {
		return GF_TRUE;
	}

	else if ((ts_begin!=-1) && (ts_end==-1) && (ts_begin>=interval->begin)) {
		return GF_TRUE;
	}
	return GF_FALSE;
}
