HandleZoneUpdateOpcode(WorldPacket& recv_data)
{
    uint32 newZone;
    recv_data >> newZone;

    DETAIL_LOG("WORLD: Received opcode CMSG_ZONEUPDATE: newzone is %u", newZone);


    uint32 newzone, newarea;
    GetPlayer()->GetZoneAndAreaId(newzone, newarea);
    GetPlayer()->UpdateZone(newzone, newarea);
}
