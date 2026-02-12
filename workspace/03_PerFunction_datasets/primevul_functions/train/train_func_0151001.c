TEST_F(ExtractorTest, TestDefaultHeaderLocationWithValidJWT) {
  auto headers =
      TestRequestHeaderMapImpl{{absl::StrCat("Authorization"), absl::StrCat("Bearer ", GoodToken)}};
  auto tokens = extractor_->extract(headers);
  EXPECT_EQ(tokens.size(), 1);


  EXPECT_EQ(tokens[0]->token(), GoodToken);
  EXPECT_TRUE(tokens[0]->isIssuerSpecified("issuer1"));
}
