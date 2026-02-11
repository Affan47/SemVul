debug(const char *place, int err, const char *fmt, ...)
{
    int e;

    if (place_should_be_logged(place) && place_is_not_logged(place) == 0) {


        if ((e = thread_to[thread_slot()])) {
            FUNCTION_GUTS_EXCL(GW_DEBUG, "");
        } else {
            FUNCTION_GUTS(GW_DEBUG, "");
        }
    }
}
