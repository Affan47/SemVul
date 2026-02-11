icaltime_from_string(const char* str)
{
    struct icaltimetype tt = icaltime_null_time();
    int size;

    icalerror_check_arg_re(str!=0,"str",icaltime_null_time());

    size = strlen(str);

    if ((size == 15) || (size == 19)) {
	tt.is_utc = 0;
	tt.is_date = 0;
    } else if ((size == 16) || (size == 20)) {
	if ((str[15] != 'Z') && (str[19] != 'Z'))
	    goto FAIL;

	tt.is_utc = 1;
	tt.zone = icaltimezone_get_utc_timezone();
	tt.is_date = 0;
    } else if ((size == 8) || (size == 10)) {
	tt.is_utc = 0;
	tt.is_date = 1;
    } else {
	goto FAIL;
    }

    if (tt.is_date == 1){
        if (size == 10) {
            char dsep1, dsep2;
            if (sscanf(str,"%04d%c%02d%c%02d",&tt.year,&dsep1,&tt.month,&dsep2,&tt.day) < 5)
                goto FAIL;
            if ((dsep1 != '-') || (dsep2 != '-'))
                goto FAIL;
        } else if (sscanf(str,"%04d%02d%02d",&tt.year,&tt.month,&tt.day) < 3) {
	    goto FAIL;
        }
    } else {
       if (size > 16 ) {
         char dsep1, dsep2, tsep, tsep1, tsep2;
         if (sscanf(str,"%04d%c%02d%c%02d%c%02d%c%02d%c%02d",&tt.year,&dsep1,&tt.month,&dsep2,
                &tt.day,&tsep,&tt.hour,&tsep1,&tt.minute,&tsep2,&tt.second) < 11)
	    goto FAIL;

	if((tsep != 'T') || (dsep1 != '-') || (dsep2 != '-') || (tsep1 != ':') || (tsep2 != ':'))
	    goto FAIL;

       } else {
	char tsep;
	if (sscanf(str,"%04d%02d%02d%c%02d%02d%02d",&tt.year,&tt.month,&tt.day,
	       &tsep,&tt.hour,&tt.minute,&tt.second) < 7)
	    goto FAIL;

	if(tsep != 'T')
	    goto FAIL;
       }
    }

    return tt;

FAIL:
    icalerror_set_errno(ICAL_MALFORMEDDATA_ERROR);
    return icaltime_null_time();
}
