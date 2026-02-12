int streamValidateListpackIntegrity(unsigned char *lp, size_t size, int deep) {
    int valid_record;
    unsigned char *p, *next;


    if (!lpValidateIntegrity(lp, size, 0, NULL, NULL))
        return 0;


    if (!deep) return 1;

    next = p = lpValidateFirst(lp);
    if (!lpValidateNext(lp, &next, size)) return 0;
    if (!p) return 0;


    int64_t entry_count = lpGetIntegerIfValid(p, &valid_record);
    if (!valid_record) return 0;
    p = next; if (!lpValidateNext(lp, &next, size)) return 0;


    int64_t deleted_count = lpGetIntegerIfValid(p, &valid_record);
    if (!valid_record) return 0;
    p = next; if (!lpValidateNext(lp, &next, size)) return 0;


    int64_t master_fields = lpGetIntegerIfValid(p, &valid_record);
    if (!valid_record) return 0;
    p = next; if (!lpValidateNext(lp, &next, size)) return 0;


    for (int64_t j = 0; j < master_fields; j++) {
        p = next; if (!lpValidateNext(lp, &next, size)) return 0;
    }


    int64_t zero = lpGetIntegerIfValid(p, &valid_record);
    if (!valid_record || zero != 0) return 0;
    p = next; if (!lpValidateNext(lp, &next, size)) return 0;

    entry_count += deleted_count;
    while (entry_count--) {
        if (!p) return 0;
        int64_t fields = master_fields, extra_fields = 3;
        int64_t flags = lpGetIntegerIfValid(p, &valid_record);
        if (!valid_record) return 0;
        p = next; if (!lpValidateNext(lp, &next, size)) return 0;


        lpGetIntegerIfValid(p, &valid_record);
        if (!valid_record) return 0;
        p = next; if (!lpValidateNext(lp, &next, size)) return 0;
        lpGetIntegerIfValid(p, &valid_record);
        if (!valid_record) return 0;
        p = next; if (!lpValidateNext(lp, &next, size)) return 0;

        if (!(flags & STREAM_ITEM_FLAG_SAMEFIELDS)) {

            fields = lpGetIntegerIfValid(p, &valid_record);
            if (!valid_record) return 0;
            p = next; if (!lpValidateNext(lp, &next, size)) return 0;


            for (int64_t j = 0; j < fields; j++) {
                p = next; if (!lpValidateNext(lp, &next, size)) return 0;
            }

            extra_fields += fields + 1;
        }


        for (int64_t j = 0; j < fields; j++) {
            p = next; if (!lpValidateNext(lp, &next, size)) return 0;
        }


        int64_t lp_count = lpGetIntegerIfValid(p, &valid_record);
        if (!valid_record) return 0;
        if (lp_count != fields + extra_fields) return 0;
        p = next; if (!lpValidateNext(lp, &next, size)) return 0;
    }

    if (next)
        return 0;

    return 1;
}
