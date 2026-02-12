TEST_F(ExtractorTest, TestPrefixHeaderMatch) {
  auto headers = TestRequestHeaderMapImpl{{"prefix-header", "AAABBBjwt_token"}};
  auto tokens = extractor_->extract(headers);
  EXPECT_EQ(tokens.size(), 2);


  EXPECT_TRUE(tokens[0]->isIssuerSpecified("issuer5"));
  EXPECT_EQ(tokens[0]->token(), "BBBjwt_token");


  EXPECT_TRUE(tokens[1]->isIssuerSpecified("issuer6"));
  EXPECT_EQ(tokens[1]->token(), "jwt_token");


  tokens[0]->removeJwt(headers);
  EXPECT_FALSE(headers.get(Http::LowerCaseString("prefix-header")));
}
