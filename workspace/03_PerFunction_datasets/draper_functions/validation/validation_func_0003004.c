HandleCharacterLevelCommand(char* args)
{
    char* nameStr = ExtractOptNotLastArg(&args);

    int32 newlevel;
    bool nolevel = false;

    if (!ExtractInt32(&args, newlevel))
    {
        if (!nameStr)
        {
            nameStr = ExtractArg(&args);
            if (!nameStr)
                return false;

            nolevel = true;
        }
        else
            return false;
    }

    Player* target;
    ObjectGuid target_guid;
    std::string target_name;
    if (!ExtractPlayerTarget(&nameStr, &target, &target_guid, &target_name))
        return false;

    int32 oldlevel = target ? target->getLevel() : Player::GetLevelFromDB(target_guid);
    if (nolevel)
        newlevel = oldlevel;

    if (newlevel < 1)
        return false;

    if (newlevel > STRONG_MAX_LEVEL)
        newlevel = STRONG_MAX_LEVEL;

    HandleCharacterLevel(target, target_guid, oldlevel, newlevel);

    if (!m_session || m_session->GetPlayer() != target)
    {
        std::string nameLink = playerLink(target_name);
        PSendSysMessage(LANG_YOU_CHANGE_LVL, nameLink.c_str(), newlevel);
    }

    return true;
}
