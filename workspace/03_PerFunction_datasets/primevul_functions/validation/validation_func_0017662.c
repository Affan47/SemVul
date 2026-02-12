void UnicodeStringTest::TestUnicodeStringInsertAppendToSelf() {
    IcuTestErrorCode status(*this, "TestUnicodeStringAppendToSelf");


    UnicodeString str(u"foo ");
    str.append(str);
    str.append(str);
    str.append(str);
    assertEquals("", u"foo foo foo foo foo foo foo foo ", str);


    str = UnicodeString(TRUE, u"foo ", 4);
    str.append(str);
    str.append(str);
    str.append(str);
    assertEquals("", u"foo foo foo foo foo foo foo foo ", str);


    str = u"abcde";
    UnicodeString sub = str.tempSubString(1, 2);
    str.append(sub);
    assertEquals("", u"abcdebc", str);


    str = UnicodeString(TRUE, u"abcde", 5);
    sub = str.tempSubString(1, 2);
    str.append(sub);
    assertEquals("", u"abcdebc", str);


    str = u"a-*b";
    str.insert(2, str);
    str.insert(4, str);
    str.insert(8, str);
    assertEquals("", u"a-a-a-a-a-a-a-a-*b*b*b*b*b*b*b*b", str);


    str = UnicodeString(TRUE, u"a-*b", 4);
    str.insert(2, str);
    str.insert(4, str);
    str.insert(8, str);
    assertEquals("", u"a-a-a-a-a-a-a-a-*b*b*b*b*b*b*b*b", str);


    str = u"abcde";
    sub = str.tempSubString(1, 3);
    str.insert(2, sub);
    assertEquals("", u"abbcdcde", str);


    str = UnicodeString(TRUE, u"abcde", 5);
    sub = str.tempSubString(1, 3);
    str.insert(2, sub);
    assertEquals("", u"abbcdcde", str);
}
