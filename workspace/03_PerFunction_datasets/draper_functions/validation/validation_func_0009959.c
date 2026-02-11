isGameOver() const
{

    if (m_score[White] + m_score[Black] == 64)
        return true;
    else
        return !(isAnyPlayerMovePossible(White) || isAnyPlayerMovePossible(Black));
}
