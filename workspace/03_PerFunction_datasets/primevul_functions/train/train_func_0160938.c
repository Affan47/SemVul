void NumberFormatTest::Test13035_MultiCodePointPaddingInPattern() {
    IcuTestErrorCode status(*this, "Test13035_MultiCodePointPaddingInPattern");
    DecimalFormat df(u"a*'நி'###0b", status);
    if (!assertSuccess("", status, true, __FILE__, __LINE__)) { return; }
    UnicodeString result;
    df.format(12, result.remove());


    df = DecimalFormat(u"a*\U0001F601###0b", status);
    if (!assertSuccess("", status, true, __FILE__, __LINE__)) { return; }
    result = df.format(12, result.remove());
    assertEquals("Single-codepoint padding should not be split", u"a\U0001F601\U0001F60112b", result, true);
    df = DecimalFormat(u"a*''###0b", status);
    if (!assertSuccess("", status, true, __FILE__, __LINE__)) { return; }
    result = df.format(12, result.remove());
    assertEquals("Quote should be escapable in padding syntax", "a''12b", result, true);
}
