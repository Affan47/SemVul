TEST_P(RemoteJwksIntegrationTest, WithGoodTokenAsyncFetchFast) {
  on_server_init_function_ = [this]() { waitForJwksResponse("200", PublicKey); };
  initializeAsyncFetchFilter(true);


  test_server_->waitForCounterGe("http.config_test.jwt_authn.jwks_fetch_success", 1);

  codec_client_ = makeHttpConnection(lookupPort("http"));

  auto response = codec_client_->makeHeaderOnlyRequest(Http::TestRequestHeaderMapImpl{
      {":method", "GET"},
      {":path", "/"},
      {":scheme", "http"},
      {":authority", "host"},
      {"Authorization", "Bearer " + std::string(GoodToken)},
  });

  waitForNextUpstreamRequest();

  const auto payload_entry =
      upstream_request_->headers().get(Http::LowerCaseString("sec-istio-auth-userinfo"));
  EXPECT_FALSE(payload_entry.empty());
  EXPECT_EQ(payload_entry[0]->value().getStringView(), ExpectedPayloadValue);

  EXPECT_TRUE(upstream_request_->headers().get(Http::CustomHeaders::get().Authorization).empty());

  upstream_request_->encodeHeaders(Http::TestResponseHeaderMapImpl{{":status", "200"}}, true);

  ASSERT_TRUE(response->waitForEndStream());
  ASSERT_TRUE(response->complete());
  EXPECT_EQ("200", response->headers().getStatusValue());

  cleanup();
}
