Sfdouble_t sh_strnum(Shell_t *shp, const char *str, char **ptr, int mode) {
    Sfdouble_t d;
    char *last;

    if (*str == 0) {
        d = 0.0;
        last = (char *)str;
    } else {
        d = number(str, &last, shp->inarith ? 0 : 10, NULL);
        if (*last && !shp->inarith && sh_isstate(shp, SH_INIT)) {

            d = number(str, &last, 0, NULL);
        }
        if (*last) {
            if (sh_isstate(shp, SH_INIT)) {


                d = 0.0;
            } else {
                if (*last != '.' || last[1] != '.') {
                    d = strval(shp, str, &last, arith, mode);
                    Varsubscript = true;
                }
                if (!ptr && *last && mode > 0) {
                    errormsg(SH_DICT, ERROR_exit(1), e_lexbadchar, *last, str);
                }
            }
        } else if (d == 0.0 && *str == '-') {
            d = -0.0;
        }
    }
    if (ptr) *ptr = last;
    return d;
}
