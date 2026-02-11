div(const DigitList &other, UErrorCode &status) {
    if (U_FAILURE(status)) {
        return;
    }
    uprv_decNumberDivide(fDecNumber, fDecNumber, other.fDecNumber, &fContext);
    internalClear();
}
