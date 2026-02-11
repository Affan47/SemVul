_create(Request& r, MethodParams& params) {
	VDate& vdate=GET_SELF(r, VDate);

	if(params.count()==1){
		if(params[0].is_string()){
			vdate.set_time(cstr_to_time_t(params[0].get_string()->cstrm()));
		} else {
			time_t t=(time_t)round(params.as_double(0, "float days must be double", r)*SECS_PER_DAY);
			if(t<0 || !localtime(&t))
				throw Exception(DATE_RANGE_EXCEPTION_TYPE,
					0,
					"invalid datetime");
			vdate.set_time(t);
		}
	} else {
		assert(params.count()<=6);
		tm tmIn; memset(&tmIn, 0, sizeof(tmIn));
		tmIn.tm_isdst=-1;
		tmIn.tm_year=to_tm_year(params.as_int(0, "year must be int", r));
		tmIn.tm_mon=params.as_int(1, "month must be int", r)-1;
		tmIn.tm_mday=params.count()>2?params.as_int(2, "mday must be int", r):1;
		int savedHour=0;
		if(params.count()>3) savedHour=tmIn.tm_hour=params.as_int(3, "hour must be int", r);
		if(params.count()>4) tmIn.tm_min=params.as_int(4, "minutes must be int", r);
		if(params.count()>5) tmIn.tm_sec=params.as_int(5, "seconds must be int", r);
		vdate.set_time(tmIn);
	};
}
