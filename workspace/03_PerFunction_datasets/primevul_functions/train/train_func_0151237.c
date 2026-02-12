TEST_F(ExtractorTest, TestMultipleTokens) {
  auto headers = TestRequestHeaderMapImpl{
      {":path", "/path?token_param=token3&access_token=token4"},
      {"token-header", "token2"},
      {"authorization", "Bearer token1"},
      {"prefix-header", "AAAtoken5"},
  };
  auto tokens = extractor_->extract(headers);
  EXPECT_EQ(tokens.size(), 5);

  EXPECT_EQ(tokens[0]->token(), "token1");
  EXPECT_EQ(tokens[1]->token(), "token5");
  EXPECT_EQ(tokens[2]->token(), "token2");
  EXPECT_EQ(tokens[3]->token(), "token4");
  EXPECT_EQ(tokens[4]->token(), "token3");
}
