void NumberFormatTest::TestCurrencyObject() {
    UErrorCode ec = U_ZERO_ERROR;
    NumberFormat* fmt =
        NumberFormat::createCurrencyInstance(Locale::getUS(), ec);

    if (U_FAILURE(ec)) {
        dataerrln("FAIL: getCurrencyInstance(US) - %s", u_errorName(ec));
        delete fmt;
        return;
    }

    Locale null("", "", "");

    expectCurrency(*fmt, null, 1234.56, "$1,234.56");

    expectCurrency(*fmt, Locale::getFrance(),
                   1234.56, CharsToUnicodeString("\\u20AC1,234.56"));

    expectCurrency(*fmt, Locale::getJapan(),
                   1234.56, CharsToUnicodeString("\\u00A51,235"));

    expectCurrency(*fmt, Locale("fr", "CH", ""),
                   1234.56, "CHF 1,234.56");

    expectCurrency(*fmt, Locale::getUS(),
                   1234.56, "$1,234.56");

    delete fmt;
    fmt = NumberFormat::createCurrencyInstance(Locale::getFrance(), ec);

    if (U_FAILURE(ec)) {
        errln("FAIL: getCurrencyInstance(FRANCE)");
        delete fmt;
        return;
    }

    expectCurrency(*fmt, null, 1234.56, CharsToUnicodeString("1\\u202F234,56 \\u20AC"));

    expectCurrency(*fmt, Locale::getJapan(),
                   1234.56, CharsToUnicodeString("1\\u202F235 JPY"));

    expectCurrency(*fmt, Locale("fr", "CH", ""),
                   1234.56, CharsToUnicodeString("1\\u202F234,56 CHF"));

    expectCurrency(*fmt, Locale::getUS(),
                   1234.56, CharsToUnicodeString("1\\u202F234,56 $US"));

    expectCurrency(*fmt, Locale::getFrance(),
                   1234.56, CharsToUnicodeString("1\\u202F234,56 \\u20AC"));

    delete fmt;
}
