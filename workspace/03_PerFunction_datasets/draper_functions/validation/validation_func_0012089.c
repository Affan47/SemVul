findPosition(const Board& position) const
{
    MoveId current = 0;
    Board currentBoard(m_startingBoard);

    for(;;)
    {
        if(currentBoard == position && currentBoard.positionIsSame(position))
        {
            return current;
        }

        current = m_moveNodes[current].nextNode;
        if(current == NO_MOVE || !position.canBeReachedFrom(currentBoard))
        {
            return NO_MOVE;
        }

        currentBoard.doMove(m_moveNodes[current].move);
    }
    return NO_MOVE;
}
