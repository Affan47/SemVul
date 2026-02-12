TEST_P(LocalJwksIntegrationTest, FilterStateRequirement) {

  const std::string auth_filter_conf = R"(
  providers:
    example_provider:
      issuer: https://example.com
      audiences:
      - example_service
  filter_state_rules:
    name: jwt_selector
    requires:
      example_provider:
        provider_name: example_provider
)";

  config_helper_.prependFilter(getAuthFilterConfig(auth_filter_conf, true));
  config_helper_.prependFilter(absl::StrCat("name: ", HeaderToFilterStateFilterName));
  initialize();

  codec_client_ = makeHttpConnection(lookupPort("http"));

  struct TestCase {
    std::vector<std::pair<std::string, std::string>> extra_headers;
    std::string expected_status;
  };

  const TestCase test_cases[] = {

      {

          {},
          "200",
      },


      {

          {
              {"jwt_selector", "example_provider"},
          },
          "401",
      },


      {

          {
              {"jwt_selector", "example_provider"},
              {"Authorization", "Bearer " + std::string(GoodToken)},
          },
          "200",
      },
  };

  for (const auto& test : test_cases) {
    Http::TestRequestHeaderMapImpl headers{
        {":method", "GET"},
        {":path", "/foo"},
        {":scheme", "http"},
        {":authority", "host"},
    };
    for (const auto& h : test.extra_headers) {
      headers.addCopy(h.first, h.second);
    }
    auto response = codec_client_->makeHeaderOnlyRequest(headers);

    if (test.expected_status == "200") {
      waitForNextUpstreamRequest();
      upstream_request_->encodeHeaders(Http::TestResponseHeaderMapImpl{{":status", "200"}}, true);
    }

    ASSERT_TRUE(response->waitForEndStream());
    ASSERT_TRUE(response->complete());
    EXPECT_EQ(test.expected_status, response->headers().getStatusValue());
  }
}
