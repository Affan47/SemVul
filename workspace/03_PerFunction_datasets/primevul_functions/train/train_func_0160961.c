void NumberFormatTest::expect2(NumberFormat& fmt, const Formattable& n, const UnicodeString& str) {

    expect(fmt, n, str, FALSE);
    expect(fmt, str, n);
}
