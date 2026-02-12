void NumberFormatTest::TestNonpositiveMultiplier() {
    UErrorCode status = U_ZERO_ERROR;
    DecimalFormatSymbols US(Locale::getUS(), status);
    CHECK(status, "DecimalFormatSymbols constructor");
    DecimalFormat df(UnicodeString("0"), US, status);
    CHECK(status, "DecimalFormat(0)");


    int32_t mult = df.getMultiplier();
    df.setMultiplier(0);
    if (df.getMultiplier() != mult) {
        errln("DecimalFormat.setMultiplier(0) did not ignore its zero input");
    }


    df.setMultiplier(-1);
    if (df.getMultiplier() != -1) {
        errln("DecimalFormat.setMultiplier(-1) ignored its negative input");
        return;
    }

    expect(df, "1122.123", -1122.123);
    expect(df, "-1122.123", 1122.123);
    expect(df, "1.2", -1.2);
    expect(df, "-1.2", 1.2);


    expect(df, U_INT64_MIN,    "9223372036854775808", FALSE);
    expect(df, U_INT64_MIN+1,  "9223372036854775807");
    expect(df, (int64_t)-123,                  "123");
    expect(df, (int64_t)123,                  "-123");
    expect(df, U_INT64_MAX-1, "-9223372036854775806");
    expect(df, U_INT64_MAX,   "-9223372036854775807");

    df.setMultiplier(-2);
    expect(df, -(U_INT64_MIN/2)-1, "-9223372036854775806");
    expect(df, -(U_INT64_MIN/2),   "-9223372036854775808");
    expect(df, -(U_INT64_MIN/2)+1, "-9223372036854775810", FALSE);

    df.setMultiplier(-7);
    expect(df, -(U_INT64_MAX/7)-1, "9223372036854775814", FALSE);
    expect(df, -(U_INT64_MAX/7),   "9223372036854775807");
    expect(df, -(U_INT64_MAX/7)+1, "9223372036854775800");


}
