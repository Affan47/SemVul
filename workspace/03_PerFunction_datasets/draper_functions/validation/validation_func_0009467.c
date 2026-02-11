SendPlayerAmbiguousNotice(const std::string &name)
{
    WorldPacket data(SMSG_CHAT_PLAYER_AMBIGUOUS, name.size() + 1);
    data << name;
    SendPacket(&data);
}
