void testSetupConnection() {


    if (GetParam().acceptZeroRtt) {
      EXPECT_CALL(connCallback, onTransportReady());
    }
    recvClientHello();


    if (!GetParam().acceptZeroRtt) {
      EXPECT_CALL(connCallback, onTransportReady());
    }

    EXPECT_CALL(routingCallback, onConnectionIdBound(_));

    expectWriteNewSessionTicket();
    recvClientFinished();
  }
