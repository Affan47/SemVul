TEST_P(PerRouteIntegrationTest, PerRouteConfigWrongRequireName) {

  const std::string filter_conf = R"(
  providers:
    example_provider:
      issuer: https://example.com
      audiences:
      - example_service
  requirement_map:
    abc:
      provider_name: "example_provider"
)";


  PerRouteConfig per_route;
  per_route.set_requirement_name("wrong-requirement-name");
  setup(filter_conf, per_route);

  codec_client_ = makeHttpConnection(lookupPort("http"));


  auto response = codec_client_->makeHeaderOnlyRequest(Http::TestRequestHeaderMapImpl{
      {":method", "GET"},
      {":path", "/"},
      {":scheme", "http"},
      {":authority", "host"},
      {"Authorization", "Bearer " + std::string(GoodToken)},
  });

  ASSERT_TRUE(response->waitForEndStream());
  ASSERT_TRUE(response->complete());
  EXPECT_EQ("403", response->headers().getStatusValue());
}
