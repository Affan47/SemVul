validateField(UCalendarDateFields field, UErrorCode &status) {
    if (field == UCAL_MONTH && !isLeapYear(handleGetExtendedYear()) && internalGet(UCAL_MONTH) == ADAR_1) {
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return;
    }
    Calendar::validateField(field, status);
}
