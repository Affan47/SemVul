TEST_F(HTTP2CodecTest, NoExHeaders) {

  SetUpUpstreamTest();

  EXPECT_EQ(callbacks_.settings, 0);
  EXPECT_EQ(callbacks_.numSettings, 0);
  EXPECT_EQ(false, downstreamCodec_.supportsExTransactions());

  parseUpstream();

  EXPECT_EQ(callbacks_.settings, 1);

  EXPECT_EQ(callbacks_.numSettings, 3);
  EXPECT_EQ(false, downstreamCodec_.supportsExTransactions());
}
