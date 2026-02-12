TEST_F(HeaderUtilityTest, RemovePortsFromHost) {
  const std::vector<std::pair<std::string, std::string>> host_headers{
      {"localhost", "localhost"},
      {"localhost:443", "localhost"},
      {"", ""},
      {":443", ""},
      {"192.168.1.1", "192.168.1.1"},
      {"192.168.1.1:443", "192.168.1.1"},
      {"[fc00::1]:443", "[fc00::1]"},
      {"[fc00::1]", "[fc00::1]"},
      {":", ":"},
      {"]:", "]:"},
      {":abc", ":abc"},
      {"localhost:80", "localhost:80"},
      {"192.168.1.1:80", "192.168.1.1:80"},
      {"[fc00::1]:80", "[fc00::1]:80"}
  };

  for (const auto& host_pair : host_headers) {
    auto& host_header = hostHeaderEntry(host_pair.first);
    HeaderUtility::stripPortFromHost(headers_, 443);
    EXPECT_EQ(host_header.value().getStringView(), host_pair.second);
  }
}
