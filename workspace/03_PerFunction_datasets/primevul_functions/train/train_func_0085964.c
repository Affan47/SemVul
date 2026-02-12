TEST(HTTP2CodecConstantsTest, HTTPContantsAreCommonHeaders) {


  EXPECT_EQ(HTTPCommonHeaders::hash(headers::kMethod),
            HTTP_HEADER_COLON_METHOD);
  EXPECT_EQ(HTTPCommonHeaders::hash(headers::kScheme),
            HTTP_HEADER_COLON_SCHEME);
  EXPECT_EQ(HTTPCommonHeaders::hash(headers::kPath),
            HTTP_HEADER_COLON_PATH);
  EXPECT_EQ(
    HTTPCommonHeaders::hash(headers::kAuthority),
    HTTP_HEADER_COLON_AUTHORITY);
  EXPECT_EQ(HTTPCommonHeaders::hash(headers::kStatus),
            HTTP_HEADER_COLON_STATUS);
}
