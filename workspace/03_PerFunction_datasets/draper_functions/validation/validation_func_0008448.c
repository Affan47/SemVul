SaveToDB(uint32 mapid, uint8 spawnMask, uint32 phaseMask)
{

    CreatureData& data = sObjectMgr.NewOrExistCreatureData(GetGUIDLow());

    uint32 displayId = GetNativeDisplayId();


    CreatureInfo const* cinfo = GetCreatureInfo();
    if (cinfo)
    {
        if (displayId != cinfo->ModelId[0] && displayId != cinfo->ModelId[1] &&
                displayId != cinfo->ModelId[2] && displayId != cinfo->ModelId[3])
        {
            for (int i = 0; i < MAX_CREATURE_MODEL && displayId; ++i)
                if (cinfo->ModelId[i])
                    if (CreatureModelInfo const* minfo = sObjectMgr.GetCreatureModelInfo(cinfo->ModelId[i]))
                        if (displayId == minfo->modelid_other_gender)
                            displayId = 0;
        }
        else
            displayId = 0;
    }


    data.id = GetEntry();
    data.mapid = mapid;
    data.spawnMask = spawnMask;
    data.phaseMask = phaseMask;
    data.modelid_override = displayId;
    data.equipmentId = GetEquipmentId();
    data.posX = GetPositionX();
    data.posY = GetPositionY();
    data.posZ = GetPositionZ();
    data.orientation = GetOrientation();
    data.spawntimesecs = m_respawnDelay;

    data.spawndist = GetDefaultMovementType() == IDLE_MOTION_TYPE ? 0 : m_respawnradius;
    data.currentwaypoint = 0;
    data.curhealth = GetHealth();
    data.curmana = GetPower(POWER_MANA);
    data.is_dead = m_isDeadByDefault;

    data.movementType = !m_respawnradius && GetDefaultMovementType() == RANDOM_MOTION_TYPE
                        ? IDLE_MOTION_TYPE : GetDefaultMovementType();


    WorldDatabase.BeginTransaction();

    WorldDatabase.PExecuteLog("DELETE FROM creature WHERE guid=%u", GetGUIDLow());

    std::ostringstream ss;
    ss << "INSERT INTO creature VALUES ("
       << GetGUIDLow() << ","
       << data.id << ","
       << data.mapid << ","
       << uint32(data.spawnMask) << ","
       << uint16(data.phaseMask) << ","
       << data.modelid_override << ","
       << data.equipmentId << ","
       << data.posX << ","
       << data.posY << ","
       << data.posZ << ","
       << data.orientation << ","
       << data.spawntimesecs << ","
       << (float) data.spawndist << ","
       << data.currentwaypoint << ","
       << data.curhealth << ","
       << data.curmana << ","
       << (data.is_dead  ? 1 : 0) << ","
       << uint32(data.movementType) << ")";

    WorldDatabase.PExecuteLog("%s", ss.str().c_str());

    WorldDatabase.CommitTransaction();
}
