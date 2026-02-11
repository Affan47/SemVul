AddToSocialList(ObjectGuid friend_guid, bool ignore)
{

    if (ignore)
    {
        if (GetNumberOfSocialsWithFlag(SOCIAL_FLAG_IGNORED) >= SOCIALMGR_IGNORE_LIMIT)
            return false;
    }
    else
    {
        if (GetNumberOfSocialsWithFlag(SOCIAL_FLAG_FRIEND) >= SOCIALMGR_FRIEND_LIMIT)
            return false;
    }

    uint32 flag = SOCIAL_FLAG_FRIEND;
    if (ignore)
        flag = SOCIAL_FLAG_IGNORED;

    PlayerSocialMap::const_iterator itr = m_playerSocialMap.find(friend_guid.GetCounter());
    if (itr != m_playerSocialMap.end())
    {
        CharacterDatabase.PExecute("UPDATE character_social SET flags = (flags | %u) WHERE guid = '%u' AND friend = '%u'", flag, m_playerLowGuid, friend_guid.GetCounter());
        m_playerSocialMap[friend_guid.GetCounter()].Flags |= flag;
    }
    else
    {
        CharacterDatabase.PExecute("INSERT INTO character_social (guid, friend, flags) VALUES ('%u', '%u', '%u')", m_playerLowGuid, friend_guid.GetCounter(), flag);
        FriendInfo fi;
        fi.Flags |= flag;
        m_playerSocialMap[friend_guid.GetCounter()] = fi;
    }
    return true;
}
