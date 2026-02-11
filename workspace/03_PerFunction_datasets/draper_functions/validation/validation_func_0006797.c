initRecognizers(UErrorCode &status) {
    U_NAMESPACE_USE
    ucln_i18n_registerCleanup(UCLN_I18N_CSDET, csdet_cleanup);
    CSRecognizerInfo *tempArray[] = {
        new CSRecognizerInfo(new CharsetRecog_UTF8(), TRUE),

        new CSRecognizerInfo(new CharsetRecog_UTF_16_BE(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_UTF_16_LE(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_UTF_32_BE(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_UTF_32_LE(), TRUE),

        new CSRecognizerInfo(new CharsetRecog_8859_1(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_8859_2(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_8859_5_ru(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_8859_6_ar(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_8859_7_el(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_8859_8_I_he(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_8859_8_he(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_windows_1251(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_windows_1256(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_KOI8_R(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_8859_9_tr(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_sjis(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_gb_18030(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_euc_jp(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_euc_kr(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_big5(), TRUE),

        new CSRecognizerInfo(new CharsetRecog_2022JP(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_2022KR(), TRUE),
        new CSRecognizerInfo(new CharsetRecog_2022CN(), TRUE),

        new CSRecognizerInfo(new CharsetRecog_IBM424_he_rtl(), FALSE),
        new CSRecognizerInfo(new CharsetRecog_IBM424_he_ltr(), FALSE),
        new CSRecognizerInfo(new CharsetRecog_IBM420_ar_rtl(), FALSE),
        new CSRecognizerInfo(new CharsetRecog_IBM420_ar_ltr(), FALSE)
    };
    int32_t rCount = ARRAY_SIZE(tempArray);

    fCSRecognizers = NEW_ARRAY(CSRecognizerInfo *, rCount);

    if (fCSRecognizers == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
    }
    else {
        fCSRecognizers_size = rCount;
        for (int32_t r = 0; r < rCount; r += 1) {
            fCSRecognizers[r] = tempArray[r];
            if (fCSRecognizers[r] == NULL) {
                status = U_MEMORY_ALLOCATION_ERROR;
            }
        }
    }
}
