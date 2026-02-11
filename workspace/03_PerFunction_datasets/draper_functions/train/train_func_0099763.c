resetTalents(bool no_cost)
{
    Unit* owner = GetOwner();
    if (!owner || owner->GetTypeId() != TYPEID_PLAYER)
        return false;


    if (((Player*)owner)->HasAtLoginFlag(AT_LOGIN_RESET_PET_TALENTS))
        ((Player*)owner)->RemoveAtLoginFlag(AT_LOGIN_RESET_PET_TALENTS, true);

    CreatureInfo const* ci = GetCreatureInfo();
    if (!ci)
        return false;

    CreatureFamilyEntry const* pet_family = sCreatureFamilyStore.LookupEntry(ci->Family);
    if (!pet_family || pet_family->petTalentType < 0)
        return false;

    Player* player = (Player*)owner;

    if (m_usedTalentCount == 0)
    {
        UpdateFreeTalentPoints(false);
        return false;
    }

    uint32 cost = 0;

    if (!no_cost)
    {
        cost = resetTalentsCost();

        if (player->GetMoney() < cost)
        {
            player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, 0, 0, 0);
            return false;
        }
    }

    for (unsigned int i = 0; i < sTalentStore.GetNumRows(); ++i)
    {
        TalentEntry const* talentInfo = sTalentStore.LookupEntry(i);

        if (!talentInfo) continue;

        TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);

        if (!talentTabInfo)
            continue;


        if (!((1 << pet_family->petTalentType) & talentTabInfo->petTalentMask))
            continue;

        for (int j = 0; j < MAX_TALENT_RANK; ++j)
            if (talentInfo->RankID[j])
                removeSpell(talentInfo->RankID[j], !IsPassiveSpell(talentInfo->RankID[j]), false);
    }

    UpdateFreeTalentPoints(false);

    if (!no_cost)
    {
        player->ModifyMoney(-(int32)cost);

        m_resetTalentsCost = cost;
        m_resetTalentsTime = time(NULL);
    }
    player->PetSpellInitialize();
    return true;
}
