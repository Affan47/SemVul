void NumberFormatTest::Test10468ApplyPattern() {

    UErrorCode status = U_ZERO_ERROR;
    DecimalFormat fmt("'I''ll'*a###.##", status);

    if (U_FAILURE(status)) {
        errcheckln(status, "DecimalFormat constructor failed - %s", u_errorName(status));
        return;
    }

    assertEquals("Padding character should be 'a'.", u"a", fmt.getPadCharacterString());


    fmt.applyPattern("AA#,##0.00ZZ", status);


    assertEquals("applyPattern did not clear padding character.", u" ", fmt.getPadCharacterString());
}
