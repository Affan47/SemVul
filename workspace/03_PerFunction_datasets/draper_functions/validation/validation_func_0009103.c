irplib_wcs_mjd_from_string(double * pmjd, const char * iso8601)
{


    int year, day, month, hour, minute;
    double second;

    return irplib_wcs_iso8601_from_string(&year, &month, &day, &hour,
                                          &minute, &second, iso8601)
        || irplib_wcs_mjd_from_iso8601(pmjd, year, month, day, hour, minute,
                                       second)
        ? cpl_error_set_where(cpl_func) : CPL_ERROR_NONE;
}
