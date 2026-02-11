CollectSearchScopes(const TokenIdxSet& searchScope,
                                           TokenIdxSet&       actualTypeScope,
                                           TokenTree*         tree)
{
    CC_LOCKER_TRACK_TT_MTX_LOCK(s_TokenTreeMutex)

    for (TokenIdxSet::const_iterator pScope=searchScope.begin(); pScope!=searchScope.end(); ++pScope)
    {
        actualTypeScope.insert(*pScope);

        if ((*pScope) != -1)
        {
            const Token* token = tree->at(*pScope);
            if (!token)
                continue;
            const Token* parent = tree->at(token->m_ParentIndex);
            while (true)
            {
                if (!parent)
                    break;
                actualTypeScope.insert(parent->m_Index);
                parent = tree->at(parent->m_ParentIndex);
            }
        }
    }

    CC_LOCKER_TRACK_TT_MTX_UNLOCK(s_TokenTreeMutex)
}
