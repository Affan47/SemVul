HandleReclaimCorpseOpcode(WorldPacket& recv_data)
{
    DETAIL_LOG("WORLD: Received opcode CMSG_RECLAIM_CORPSE");

    ObjectGuid guid;
    recv_data >> guid;

    if (GetPlayer()->IsAlive())
        { return; }


    if (!GetPlayer()->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
        { return; }

    Corpse* corpse = GetPlayer()->GetCorpse();

    if (!corpse)
        { return; }


    if (corpse->GetGhostTime() + GetPlayer()->GetCorpseReclaimDelay(corpse->GetType() == CORPSE_RESURRECTABLE_PVP) > time(NULL))
        { return; }

    if (!corpse->IsWithinDistInMap(GetPlayer(), CORPSE_RECLAIM_RADIUS, true))
        { return; }


    GetPlayer()->ResurrectPlayer(GetPlayer()->InBattleGround() ? 1.0f : 0.5f);


    GetPlayer()->SpawnCorpseBones();
}
