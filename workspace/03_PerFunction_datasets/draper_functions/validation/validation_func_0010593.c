updateTerminated(Board*)
{
    if(m_bRequestPending)
    {
        emit openingTreeUpdateStarted();
        m_bRequestPending = false;
        connect(&oupd, SIGNAL(UpdateFinished(Board*)), this, SLOT(updateFinished(Board*)), Qt::UniqueConnection);
        connect(&oupd, SIGNAL(UpdateTerminated(Board*)), this, SLOT(updateTerminated(Board*)), Qt::UniqueConnection);
        connect(&oupd, SIGNAL(progress(int)), SIGNAL(progress(int)), Qt::UniqueConnection);
        oupd.updateFilter(*m_filter, m_board, m_moves, m_games, m_updateFilter, m_bEnd);
    }
}
