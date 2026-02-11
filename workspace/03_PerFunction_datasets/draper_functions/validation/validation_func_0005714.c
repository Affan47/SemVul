ApplyModeFlags(PetModeFlags mode, bool apply)
{
    if (apply)
        { m_petModeFlags = PetModeFlags(m_petModeFlags | mode); }
    else
        { m_petModeFlags = PetModeFlags(m_petModeFlags & ~mode); }

    Unit* owner = GetOwner();
    if (!owner || owner->GetTypeId() != TYPEID_PLAYER)
        { return; }

    WorldPacket data(SMSG_PET_MODE, 12);
    data << GetObjectGuid();
    data << uint32(m_petModeFlags);
    ((Player*)owner)->GetSession()->SendPacket(&data);
}
