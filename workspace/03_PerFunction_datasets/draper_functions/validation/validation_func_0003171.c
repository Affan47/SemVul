ChangeLeader(ObjectGuid guid)
{
    member_citerator slot = _getMemberCSlot(guid);
    if (slot == m_memberSlots.end())
        { return; }


    sEluna->OnChangeLeader(this, guid, GetLeaderGuid());

    _setLeader(guid);

    WorldPacket data(SMSG_GROUP_SET_LEADER, slot->name.size() + 1);
    data << slot->name;
    BroadcastPacket(&data, true);
    SendUpdate();
}
