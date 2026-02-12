TEST_F(HTTP2CodecTest, TestMultipleDifferentContentLengthHeaders) {


  HTTPMessage req = getPostRequest();
  req.getHeaders().add(HTTP_HEADER_CONTENT_LENGTH, "300");
  EXPECT_EQ(req.getHeaders().getNumberOfValues(HTTP_HEADER_CONTENT_LENGTH), 2);

  upstreamCodec_.generateHeader(output_, 1, req, true );
  parse();


  EXPECT_EQ(callbacks_.streamErrors, 1);
  EXPECT_EQ(callbacks_.headersComplete, 0);
  EXPECT_EQ(callbacks_.lastParseError->getHttpStatusCode(), 400);
}
