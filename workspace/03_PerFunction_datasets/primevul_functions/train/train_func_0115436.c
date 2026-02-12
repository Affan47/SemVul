int Timestamp::read(struct tm* tm)
    {
        int rc = 1;
        time_t t = mktime(tm);
        if (t != (time_t)-1) {
            rc = 0;
            actime_ = t;
            modtime_ = t;
        }
        return rc;
    }
