TEST_F(HTTP2CodecTest, HTTP2EnableConnect) {
  SetUpUpstreamTest();

  auto ws_enable = upstreamCodec_.getEgressSettings()->getSetting(
      SettingsId::ENABLE_CONNECT_PROTOCOL);

  upstreamCodec_.getEgressSettings()->setSetting(
      SettingsId::ENABLE_CONNECT_PROTOCOL, 1);
  ws_enable = upstreamCodec_.getEgressSettings()->getSetting(
      SettingsId::ENABLE_CONNECT_PROTOCOL);
  EXPECT_EQ(ws_enable->value, 1);


  upstreamCodec_.generateSettings(output_);
  parseUpstream();
  EXPECT_EQ(1, upstreamCodec_.peerHasWebsockets());
}
