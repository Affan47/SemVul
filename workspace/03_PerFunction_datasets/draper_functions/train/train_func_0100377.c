GetScriptCommandObject(const ObjectGuid guid, bool includeItem, Object*& resultObject)
{
    resultObject = NULL;

    if (!guid)
        return true;

    switch (guid.GetHigh())
    {
        case HIGHGUID_UNIT:
        case HIGHGUID_VEHICLE:
            resultObject = m_map->GetCreature(guid);
            break;
        case HIGHGUID_PET:
            resultObject = m_map->GetPet(guid);
            break;
        case HIGHGUID_PLAYER:
            resultObject = m_map->GetPlayer(guid);
            break;
        case HIGHGUID_GAMEOBJECT:
            resultObject = m_map->GetGameObject(guid);
            break;
        case HIGHGUID_CORPSE:
            resultObject = HashMapHolder<Corpse>::Find(guid);
            break;
        case HIGHGUID_ITEM:

        {
            if (includeItem)
            {
                if (Player* player = m_map->GetPlayer(m_ownerGuid))
                    resultObject = player->GetItemByGuid(guid);
                break;
            }

        }
        default:
            sLog.outErrorDb(" DB-SCRIPTS: Process table `%s` id %u, command %u with unsupported guid %s, skipping", m_table, m_script->id, m_script->command, guid.GetString().c_str());
            return false;
    }

    if (resultObject && !resultObject->IsInWorld())
        resultObject = NULL;

    return true;
}
