getTimeZoneRules(const InitialTimeZoneRule*& initial,
                                    const TimeZoneRule* trsrules[],
                                    int32_t& trscount,
                                    UErrorCode& status) const {
    if (U_FAILURE(status)) {
        return;
    }

    initial = fInitialRule;


    int32_t cnt = 0;
    int32_t idx;
    if (fHistoricRules != NULL && cnt < trscount) {
        int32_t historicCount = fHistoricRules->size();
        idx = 0;
        while (cnt < trscount && idx < historicCount) {
            trsrules[cnt++] = (const TimeZoneRule*)fHistoricRules->elementAt(idx++);
        }
    }
    if (fFinalRules != NULL && cnt < trscount) {
        int32_t finalCount = fFinalRules->size();
        idx = 0;
        while (cnt < trscount && idx < finalCount) {
            trsrules[cnt++] = (const TimeZoneRule*)fFinalRules->elementAt(idx++);
        }
    }

    trscount = cnt;
}
