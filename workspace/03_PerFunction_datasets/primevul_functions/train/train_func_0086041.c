TEST_F(HTTP2CodecTest, HTTP2SettingsFailure) {
  HTTPMessage req = getGetRequest("/guacamole");

  EXPECT_FALSE(downstreamCodec_.onIngressUpgradeMessage(req));

  HTTPHeaders& headers = req.getHeaders();


  headers.set(http2::kProtocolSettingsHeader, "????");
  EXPECT_FALSE(downstreamCodec_.onIngressUpgradeMessage(req));
  headers.set(http2::kProtocolSettingsHeader, "AAA");
  EXPECT_FALSE(downstreamCodec_.onIngressUpgradeMessage(req));


  string bigSettings((http2::kMaxFramePayloadLength + 1) * 4 / 3, 'A');
  headers.set(http2::kProtocolSettingsHeader, bigSettings);
  EXPECT_FALSE(downstreamCodec_.onIngressUpgradeMessage(req));


  headers.set(http2::kProtocolSettingsHeader, "AAAA");
  EXPECT_FALSE(downstreamCodec_.onIngressUpgradeMessage(req));


  headers.set(http2::kProtocolSettingsHeader, "AAAAAAAA");
  headers.add(http2::kProtocolSettingsHeader, "AAAAAAAA");
  EXPECT_FALSE(downstreamCodec_.onIngressUpgradeMessage(req));
}
