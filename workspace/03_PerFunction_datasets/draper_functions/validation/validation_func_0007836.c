CreateNewBattleGround(BattleGroundTypeId bgTypeId, PvPDifficultyEntry const* bracketEntry, ArenaType arenaType, bool isRated)
{

    BattleGround* bg_template = GetBattleGroundTemplate(bgTypeId);
    if (!bg_template)
    {
        sLog.outError("BattleGround: CreateNewBattleGround - bg template not found for %u", bgTypeId);
        return NULL;
    }


    if (bg_template->isArena())
    {
        BattleGroundTypeId arenas[] = { BATTLEGROUND_NA, BATTLEGROUND_BE, BATTLEGROUND_RL };
        bgTypeId = arenas[urand(0, countof(arenas) - 1)];
        bg_template = GetBattleGroundTemplate(bgTypeId);
        if (!bg_template)
        {
            sLog.outError("BattleGround: CreateNewBattleGround - bg template not found for %u", bgTypeId);
            return NULL;
        }
    }

    BattleGround* bg = NULL;

    switch (bgTypeId)
    {
        case BATTLEGROUND_AV:
            bg = new BattleGroundAV(*(BattleGroundAV*)bg_template);
            break;
        case BATTLEGROUND_WS:
            bg = new BattleGroundWS(*(BattleGroundWS*)bg_template);
            break;
        case BATTLEGROUND_AB:
            bg = new BattleGroundAB(*(BattleGroundAB*)bg_template);
            break;
        case BATTLEGROUND_NA:
            bg = new BattleGroundNA(*(BattleGroundNA*)bg_template);
            break;
        case BATTLEGROUND_BE:
            bg = new BattleGroundBE(*(BattleGroundBE*)bg_template);
            break;
        case BATTLEGROUND_AA:
            bg = new BattleGroundAA(*(BattleGroundAA*)bg_template);
            break;
        case BATTLEGROUND_EY:
            bg = new BattleGroundEY(*(BattleGroundEY*)bg_template);
            break;
        case BATTLEGROUND_RL:
            bg = new BattleGroundRL(*(BattleGroundRL*)bg_template);
            break;
        case BATTLEGROUND_SA:
            bg = new BattleGroundSA(*(BattleGroundSA*)bg_template);
            break;
        case BATTLEGROUND_DS:
            bg = new BattleGroundDS(*(BattleGroundDS*)bg_template);
            break;
        case BATTLEGROUND_RV:
            bg = new BattleGroundRV(*(BattleGroundRV*)bg_template);
            break;
        case BATTLEGROUND_IC:
            bg = new BattleGroundIC(*(BattleGroundIC*)bg_template);
            break;
        case BATTLEGROUND_RB:
            bg = new BattleGroundRB(*(BattleGroundRB*)bg_template);
            break;
        default:

            return 0;
    }


    bg->SetBracket(bracketEntry);


    sMapMgr.CreateBgMap(bg->GetMapId(), bg);

    bg->SetClientInstanceID(CreateClientVisibleInstanceId(bgTypeId, bracketEntry->GetBracketId()));


    bg->Reset();


    bg->SetStatus(STATUS_WAIT_JOIN);
    bg->SetArenaType(arenaType);
    bg->SetRated(isRated);

    return bg;
}
