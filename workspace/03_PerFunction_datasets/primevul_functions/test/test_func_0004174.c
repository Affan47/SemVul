TEST_P(QuicServerTransportHandshakeTest, TestD6DStartCallback) {
  Observer::Config config = {};
  config.pmtuEvents = true;
  auto mockObserver = std::make_unique<MockObserver>(config);
  server->addObserver(mockObserver.get());

  auto codec = std::make_unique<QuicReadCodec>(QuicNodeType::Server);
  codec->setOneRttReadCipher(createNoOpAead());
  server->getNonConstConn().readCodec = std::move(codec);

  server->getNonConstConn().d6d.state = D6DMachineState::BASE;
  EXPECT_CALL(*mockObserver, pmtuProbingStarted(_)).Times(1);

  recvClientHello();
  server->removeObserver(mockObserver.get());
}
