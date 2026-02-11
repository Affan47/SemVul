local_tz_offset(time_t date, bool current UNUSED)
{
    struct tm *tm;
#if !HAVE_STRUCT_TM_TM_GMTOFF
    struct tm local, gmt;
    long offset;
#endif

    tm = localtime(&date);

#if !HAVE_STRUCT_TM_TM_GMTOFF && HAVE_DECL_ALTZONE
    if (current)
        return (tm->tm_isdst > 0) ? -altzone : -timezone;
#endif

#if HAVE_STRUCT_TM_TM_GMTOFF
    return tm->tm_gmtoff;
#else


    local = *tm;
    tm = gmtime(&date);
    gmt = *tm;
    offset = local.tm_yday - gmt.tm_yday;
    if (offset < -1) {

        offset = 24;
    } else if (offset > 1) {

        offset = -24;
    } else {
        offset *= 24;
    }
    offset += local.tm_hour - gmt.tm_hour;
    offset *= 60;
    offset += local.tm_min - gmt.tm_min;
    return offset * 60;
#endif
}
