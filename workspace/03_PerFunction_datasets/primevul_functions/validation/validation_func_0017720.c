void UnicodeStringTest::TestLargeAppend() {
    if(quick) return;

    IcuTestErrorCode status(*this, "TestLargeAppend");

    int32_t len = 0xAFFFFFF;
    UnicodeString str;
    char16_t *buf = str.getBuffer(len);


    uprv_memset(buf, 0x4e, len * 2);
    str.releaseBuffer(len);
    UnicodeString dest;


    int64_t total = 0;
    for (int32_t i = 0; i < 16; i++) {
        dest.append(str);
        total += len;
        if (total <= INT32_MAX) {
            assertFalse("dest is not bogus", dest.isBogus());
        } else {
            assertTrue("dest should be bogus", dest.isBogus());
        }
    }
    dest.remove();
    total = 0;
    for (int32_t i = 0; i < 16; i++) {
        dest.append(str);
        total += len;
        if (total + len <= INT32_MAX) {
            assertFalse("dest is not bogus", dest.isBogus());
        } else if (total <= INT32_MAX) {

            UnicodeString str2;
            int32_t remain = INT32_MAX - total;
            char16_t *buf2 = str2.getBuffer(remain);
            if (buf2 == nullptr) {

                return;
            }
            uprv_memset(buf2, 0x4e, remain * 2);
            str2.releaseBuffer(remain);
            dest.append(str2);
            total += remain;
            assertEquals("When a string of exactly the maximum size works", (int64_t)INT32_MAX, total);
            assertEquals("When a string of exactly the maximum size works", INT32_MAX, dest.length());
            assertFalse("dest is not bogus", dest.isBogus());


            str2.truncate(1);
            dest.append(str2);
            total++;
            assertTrue("dest should be bogus", dest.isBogus());
        } else {
            assertTrue("dest should be bogus", dest.isBogus());
        }
    }
}
