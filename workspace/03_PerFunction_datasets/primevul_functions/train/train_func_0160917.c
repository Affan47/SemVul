void NumberFormatTest::Test11897_LocalizedPatternSeparator() {
    IcuTestErrorCode status(*this, "Test11897_LocalizedPatternSeparator");


    {
        DecimalFormatSymbols dfs("ar", status);
        assertEquals("pattern separator symbol should be ;",
                u";",
                dfs.getSymbol(DecimalFormatSymbols::kPatternSeparatorSymbol));
    }


    {
        DecimalFormatSymbols dfs("en", status);
        dfs.setSymbol(DecimalFormatSymbols::kPatternSeparatorSymbol, u"!", FALSE);
        DecimalFormat df(u"0", dfs, status);
        if (!assertSuccess("", status, true, __FILE__, __LINE__)) { return; }
        df.applyPattern("a0;b0", status);
        UnicodeString result;
        assertEquals("should apply the normal pattern",
                df.getNegativePrefix(result.remove()),
                "b");
        df.applyLocalizedPattern(u"c0!d0", status);
        assertEquals("should apply the localized pattern",
                df.getNegativePrefix(result.remove()),
                "d");
    }
}
