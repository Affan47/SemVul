TEST_F(HTTP2CodecTest, InvalidExHeadersSetting) {

  downstreamCodec_.getEgressSettings()->setSetting(
      SettingsId::ENABLE_EX_HEADERS, 1);


  http2::writeSettings(output_,
                      {SettingPair(SettingsId::ENABLE_EX_HEADERS, 110)});
  parse();

  EXPECT_EQ(callbacks_.sessionErrors, 1);
}
