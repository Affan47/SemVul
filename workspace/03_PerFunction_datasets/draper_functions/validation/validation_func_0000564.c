restartGame()
{
    m_board->setUpdatesEnabled(false);
    while (m_board->canUndo()) {
        m_board->undo();
    }
    m_board->resetRedo();
    m_board->resetTimer();
    setCheatModeEnabled(false);
    m_board->setGameOverEnabled(false);
    m_board->setGameStuckEnabled(false);
    m_board->setUpdatesEnabled(true);
    updateItems();
}
