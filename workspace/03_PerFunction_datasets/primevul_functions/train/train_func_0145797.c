get_zonename(struct tm *tmp)
{
#if defined(_WIN32)


	return _tzname[tmp->tm_isdst];
#else


# if defined(HAVE_STRUCT_TM_TM_ZONE)
	return tmp->tm_zone;
# else
	if ((tmp->tm_isdst != 0) && (tmp->tm_isdst != 1)) {
		return "???";
	}
#  if defined(HAVE_TZNAME)
	return tzname[tmp->tm_isdst];
#  else
	return tmp->tm_isdst ? "?DT" : "?ST";
#  endif
# endif
#endif
}
