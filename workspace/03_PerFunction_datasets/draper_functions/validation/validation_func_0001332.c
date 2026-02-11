SendWeatherUpdateToPlayer(Player* player)
{
    uint32 sound = GetSound();
    WorldPacket data(SMSG_WEATHER, (4 + 4 + 4));

    data << (uint32)m_type << (float)m_grade << (uint32)sound;
    player->GetSession()->SendPacket(&data);
}
