SaveToDB()
{
    static SqlStatementID delComplAchievements ;
    static SqlStatementID insComplAchievements ;
    static SqlStatementID delProgress ;
    static SqlStatementID insProgress ;

    if (!m_completedAchievements.empty())
    {

        for (CompletedAchievementMap::iterator iter = m_completedAchievements.begin(); iter != m_completedAchievements.end(); ++iter)
        {
            if (!iter->second.changed)
                continue;


            iter->second.changed = false;

            SqlStatement stmt = CharacterDatabase.CreateStatement(delComplAchievements, "DELETE FROM character_achievement WHERE guid = ? AND achievement = ?");
            stmt.PExecute(GetPlayer()->GetGUIDLow(), iter->first);

            stmt = CharacterDatabase.CreateStatement(insComplAchievements, "INSERT INTO character_achievement (guid, achievement, date) VALUES (?, ?, ?)");
            stmt.PExecute(GetPlayer()->GetGUIDLow(), iter->first, uint64(iter->second.date));
        }
    }

    if (!m_criteriaProgress.empty())
    {

        for (CriteriaProgressMap::iterator iter = m_criteriaProgress.begin(); iter != m_criteriaProgress.end(); ++iter)
        {
            if (!iter->second.changed)
                continue;


            iter->second.changed = false;


            SqlStatement stmt = CharacterDatabase.CreateStatement(delProgress, "DELETE FROM character_achievement_progress WHERE guid = ? AND criteria = ?");
            stmt.PExecute(GetPlayer()->GetGUIDLow(), iter->first);

            bool needSave = iter->second.counter != 0;
            if (!needSave)
            {
                AchievementCriteriaEntry const* criteria = sAchievementCriteriaStore.LookupEntry(iter->first);
                needSave = criteria && criteria->timeLimit > 0;
            }

            if (needSave)
            {
                stmt = CharacterDatabase.CreateStatement(insProgress, "INSERT INTO character_achievement_progress (guid, criteria, counter, date) VALUES (?, ?, ?, ?)");
                stmt.PExecute(GetPlayer()->GetGUIDLow(), iter->first, iter->second.counter, uint64(iter->second.date));
            }
        }
    }
}
