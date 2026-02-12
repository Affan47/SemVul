void NumberFormatTest::Test12567() {
    IcuTestErrorCode errorCode(*this, "Test12567");

    LocalPointer<DecimalFormat> df1((DecimalFormat *)
        NumberFormat::createInstance(Locale::getUS(), UNUM_CURRENCY, errorCode));
    LocalPointer<DecimalFormat> df2((DecimalFormat *)
        NumberFormat::createInstance(Locale::getUS(), UNUM_DECIMAL, errorCode));
    if (!assertSuccess("", errorCode, true, __FILE__, __LINE__)) { return; }

    df1->applyPattern(u"0.00", errorCode);
    df2->applyPattern(u"0.00", errorCode);
    assertTrue("df1 == df2", *df1 == *df2);
    assertTrue("df2 == df1", *df2 == *df1);
    df2->setPositivePrefix(u"abc");
    assertTrue("df1 != df2", *df1 != *df2);
    assertTrue("df2 != df1", *df2 != *df1);
}
