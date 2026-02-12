TEST(MatchHeadersTest, MayMatchOneOrMoreRequestHeader) {
  TestRequestHeaderMapImpl headers{{"some-header", "a"}, {"other-header", "b"}};

  const std::string yaml = R"EOF(
name: match-header
regex_match: (a|b)
  )EOF";

  std::vector<HeaderUtility::HeaderDataPtr> header_data;
  header_data.push_back(
      std::make_unique<HeaderUtility::HeaderData>(parseHeaderMatcherFromYaml(yaml)));
  EXPECT_FALSE(HeaderUtility::matchHeaders(headers, header_data));

  headers.addCopy("match-header", "a");

  EXPECT_TRUE(HeaderUtility::matchHeaders(headers, header_data));

  headers.addCopy("match-header", "b");

  EXPECT_FALSE(HeaderUtility::matchHeaders(headers, header_data));

  header_data[0] = std::make_unique<HeaderUtility::HeaderData>(parseHeaderMatcherFromYaml(R"EOF(
name: match-header
exact_match: a,b
  )EOF"));

  EXPECT_TRUE(HeaderUtility::matchHeaders(headers, header_data));

  TestScopedRuntime runtime;
  Runtime::LoaderSingleton::getExisting()->mergeValues(
      {{"envoy.reloadable_features.http_match_on_all_headers", "false"}});


  EXPECT_FALSE(HeaderUtility::matchHeaders(headers, header_data));

  header_data[0] = std::make_unique<HeaderUtility::HeaderData>(parseHeaderMatcherFromYaml(R"EOF(
name: match-header
exact_match: a
  )EOF"));

  EXPECT_TRUE(HeaderUtility::matchHeaders(headers, header_data));
}
