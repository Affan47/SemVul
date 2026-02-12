TEST_F(HTTP2CodecTest, ZeroWindow) {
  auto streamID = HTTPCodec::StreamID(1);


  upstreamCodec_.generateWindowUpdate(output_, streamID, 1);
  output_.trimEnd(http2::kFrameWindowUpdateSize);
  QueueAppender appender(&output_, http2::kFrameWindowUpdateSize);
  appender.writeBE<uint32_t>(0);

  parse();

  EXPECT_EQ(callbacks_.windowUpdateCalls, 0);
  EXPECT_EQ(callbacks_.streamErrors, 1);
  EXPECT_EQ(callbacks_.lastParseError->getCodecStatusCode(),
      ErrorCode::PROTOCOL_ERROR);
}
