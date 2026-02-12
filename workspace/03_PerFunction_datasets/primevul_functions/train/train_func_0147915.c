lyp_check_date(struct ly_ctx *ctx, const char *date)
{
    int i;
    struct tm tm, tm_;
    char *r;

    assert(date);


    for (i = 0; i < LY_REV_SIZE - 1; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') {
                goto error;
            }
        } else if (!isdigit(date[i])) {
            goto error;
        }
    }


    memset(&tm, 0, sizeof tm);
    r = strptime(date, "%Y-%m-%d", &tm);
    if (!r || r != &date[LY_REV_SIZE - 1]) {
        goto error;
    }

    tm.tm_hour = 12;

    memcpy(&tm_, &tm, sizeof tm);
    mktime(&tm_);
    if (tm.tm_mday != tm_.tm_mday) {


        goto error;
    }

    return EXIT_SUCCESS;

error:
    LOGVAL(ctx, LYE_INDATE, LY_VLOG_NONE, NULL, date);
    return EXIT_FAILURE;
}
