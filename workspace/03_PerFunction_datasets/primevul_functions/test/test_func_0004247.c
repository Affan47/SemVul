TEST_F(QuicServerTransportTest, IdleTimerNotResetWhenDataOutstanding) {


  server->getNonConstConn().outstandings.packets.clear();
  server->getNonConstConn().receivedNewPacketBeforeWrite = false;
  server->getNonConstConn().outstandings.packets.clear();
  StreamId streamId = server->createBidirectionalStream().value();

  server->idleTimeout().cancelTimeout();
  ASSERT_FALSE(server->idleTimeout().isScheduled());
  server->writeChain(
      streamId,
      IOBuf::copyBuffer("And if the darkness is to keep us apart"),
      false);
  loopForWrites();

  EXPECT_TRUE(server->idleTimeout().isScheduled());


  server->idleTimeout().cancelTimeout();
  EXPECT_FALSE(server->idleTimeout().isScheduled());
  server->writeChain(
      streamId,
      IOBuf::copyBuffer("And if the daylight feels like it's a long way off"),
      false);
  loopForWrites();
  EXPECT_FALSE(server->idleTimeout().isScheduled());
}
