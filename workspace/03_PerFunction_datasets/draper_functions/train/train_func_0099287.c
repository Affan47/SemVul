UpdatePlayerScore(Player* source, uint32 type, uint32 value)
{
    BattleGroundScoreMap::iterator itr = m_PlayerScores.find(source->GetObjectGuid());

    if (itr == m_PlayerScores.end())
        return;

    BattleGround::UpdatePlayerScore(source, type, value);
}
