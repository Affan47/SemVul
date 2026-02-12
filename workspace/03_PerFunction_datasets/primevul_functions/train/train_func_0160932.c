void NumberFormatTest::TestCurrencyNames(void) {


    UErrorCode ec = U_ZERO_ERROR;
    static const UChar USD[] = {0x55, 0x53, 0x44, 0};
    static const UChar USX[] = {0x55, 0x53, 0x58, 0};
    static const UChar CAD[] = {0x43, 0x41, 0x44, 0};
    static const UChar ITL[] = {0x49, 0x54, 0x4C, 0};
    UBool isChoiceFormat;
    int32_t len;
    const UBool possibleDataError = TRUE;


    assertEquals("USD.getName(SYMBOL_NAME, en)",
                 UnicodeString("$"),
                 UnicodeString(ucurr_getName(USD, "en",
                                             UCURR_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("USD.getName(NARROW_SYMBOL_NAME, en)",
                 UnicodeString("$"),
                 UnicodeString(ucurr_getName(USD, "en",
                                             UCURR_NARROW_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("USD.getName(LONG_NAME, en)",
                 UnicodeString("US Dollar"),
                 UnicodeString(ucurr_getName(USD, "en",
                                             UCURR_LONG_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("CAD.getName(SYMBOL_NAME, en)",
                 UnicodeString("CA$"),
                 UnicodeString(ucurr_getName(CAD, "en",
                                             UCURR_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("CAD.getName(NARROW_SYMBOL_NAME, en)",
                 UnicodeString("$"),
                 UnicodeString(ucurr_getName(CAD, "en",
                                             UCURR_NARROW_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("CAD.getName(SYMBOL_NAME, en_CA)",
                 UnicodeString("$"),
                 UnicodeString(ucurr_getName(CAD, "en_CA",
                                             UCURR_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("USD.getName(SYMBOL_NAME, en_CA)",
                 UnicodeString("US$"),
                 UnicodeString(ucurr_getName(USD, "en_CA",
                                             UCURR_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("USD.getName(NARROW_SYMBOL_NAME, en_CA)",
                 UnicodeString("$"),
                 UnicodeString(ucurr_getName(USD, "en_CA",
                                             UCURR_NARROW_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("USD.getName(SYMBOL_NAME) in en_NZ",
                 UnicodeString("US$"),
                 UnicodeString(ucurr_getName(USD, "en_NZ",
                                             UCURR_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("CAD.getName(SYMBOL_NAME)",
                 UnicodeString("CA$"),
                 UnicodeString(ucurr_getName(CAD, "en_NZ",
                                             UCURR_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("USX.getName(SYMBOL_NAME)",
                 UnicodeString("USX"),
                 UnicodeString(ucurr_getName(USX, "en_US",
                                             UCURR_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("USX.getName(NARROW_SYMBOL_NAME)",
                 UnicodeString("USX"),
                 UnicodeString(ucurr_getName(USX, "en_US",
                                             UCURR_NARROW_SYMBOL_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertEquals("USX.getName(LONG_NAME)",
                 UnicodeString("USX"),
                 UnicodeString(ucurr_getName(USX, "en_US",
                                             UCURR_LONG_NAME,
                                             &isChoiceFormat, &len, &ec)),
                                             possibleDataError);
    assertSuccess("ucurr_getName", ec);

    ec = U_ZERO_ERROR;


    ucurr_getName(CAD, "es_ES", UCURR_LONG_NAME, &isChoiceFormat,
                            &len, &ec);
    assertTrue("ucurr_getName (es_ES fallback)",
                    U_USING_FALLBACK_WARNING == ec, TRUE, possibleDataError);

    ucurr_getName(CAD, "zh_TW", UCURR_LONG_NAME, &isChoiceFormat,
                            &len, &ec);
    assertTrue("ucurr_getName (zh_TW fallback)",
                    U_USING_FALLBACK_WARNING == ec, TRUE, possibleDataError);

    ucurr_getName(CAD, "en_US", UCURR_LONG_NAME, &isChoiceFormat,
                            &len, &ec);
    assertTrue("ucurr_getName (en_US default)",
                    U_USING_DEFAULT_WARNING == ec || U_USING_FALLBACK_WARNING == ec, TRUE);

    ucurr_getName(CAD, "ti", UCURR_LONG_NAME, &isChoiceFormat,
                            &len, &ec);
    assertTrue("ucurr_getName (ti default)",
                    U_USING_DEFAULT_WARNING == ec, TRUE);


    ucurr_getName(ITL, "cy", UCURR_LONG_NAME, &isChoiceFormat,
                            &len, &ec);
    assertTrue("ucurr_getName (cy default to root)",
                    U_USING_DEFAULT_WARNING == ec, TRUE);


}
