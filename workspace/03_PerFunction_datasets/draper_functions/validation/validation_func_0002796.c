parse_time( char *atm )
{
	struct lutil_tm tm;
	struct lutil_timet tt;
	time_t ret = (time_t)-1;

	if ( lutil_parsetime( atm, &tm ) == 0) {
		lutil_tm2time( &tm, &tt );
		ret = tt.tt_sec;
	}
	return ret;
}
