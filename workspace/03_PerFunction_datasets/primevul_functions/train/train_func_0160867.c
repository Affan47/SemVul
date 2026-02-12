void NumberFormatTest::expect3(NumberFormat& fmt, const Formattable& n, const UnicodeString& str) {

    expect_rbnf(fmt, n, str, FALSE);
    expect_rbnf(fmt, str, n);
}
