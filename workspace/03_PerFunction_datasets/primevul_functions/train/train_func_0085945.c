TEST_F(HTTP2CodecTest, HTTP2SettingsSuccess) {
  HTTPMessage req = getGetRequest("/guacamole");


  req.getHeaders().add(http2::kProtocolSettingsHeader, "");
  EXPECT_TRUE(downstreamCodec_.onIngressUpgradeMessage(req));


  HTTP2Codec::requestUpgrade(req);
  EXPECT_TRUE(downstreamCodec_.onIngressUpgradeMessage(req));
}
