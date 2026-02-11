HandleBanInfoCharacterCommand(char* args)
{
    Player* target;
    ObjectGuid target_guid;
    if (!ExtractPlayerTarget(&args, &target, &target_guid))
        { return false; }

    uint32 accountid = target ? target->GetSession()->GetAccountId() : sObjectMgr.GetPlayerAccountIdByGUID(target_guid);

    std::string accountname;
    if (!sAccountMgr.GetName(accountid, accountname))
    {
        PSendSysMessage(LANG_BANINFO_NOCHARACTER);
        return true;
    }

    return HandleBanInfoHelper(accountid, accountname.c_str());
}
