TEST_F(QuicUnencryptedServerTransportTest, TestBadPacketProtectionLevel) {

  auto packet = VersionNegotiationPacketBuilder(
                    *clientConnectionId ,
                    getTestConnectionId(1) ,
                    {QuicVersion::MVFST})
                    .buildPacket();
  EXPECT_CALL(*transportInfoCb_, onPacketDropped(_));
  deliverData(packet.second->clone());
}
