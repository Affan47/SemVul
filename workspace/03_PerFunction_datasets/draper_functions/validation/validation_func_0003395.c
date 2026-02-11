loadGame(const QString &fileName)
{
    if (!fileName.isEmpty() && QFile(fileName).exists()) {
        m_game->start(Preferences::engineCommand());

        m_gameScene->showTerritory(false);
        m_gameView->setInteractive(false);

        m_newGameAction->setEnabled(true);
        m_loadGameAction->setEnabled(true);
        m_saveAction->setEnabled(false);
        m_startGameAction->setEnabled(true);
        m_finishGameAction->setEnabled(false);

        m_undoMoveAction->setEnabled(false);
        m_redoMoveAction->setEnabled(false);
        m_passMoveAction->setEnabled(false);
        m_hintAction->setEnabled(false);

        disconnect(m_game, SIGNAL(canRedoChanged(bool)), m_redoMoveAction, SLOT(setEnabled(bool)));
        disconnect(m_game, SIGNAL(canUndoChanged(bool)), m_undoMoveAction, SLOT(setEnabled(bool)));
        disconnect(m_game, SIGNAL(currentPlayerChanged(Player)), this, SLOT(playerChanged()));

        m_gameDock->setVisible(false);
        m_gameDock->toggleViewAction()->setEnabled(false);
        m_movesDock->setVisible(false);
        m_movesDock->toggleViewAction()->setEnabled(false);
        m_setupDock->setVisible(true);
        m_errorDock->setVisible(false);

        m_setupWidget->loadedGame(fileName);
        m_gameScene->showMessage(i18n("Set up a loaded game..."));
        return true;
    } else {
        m_gameScene->showMessage(i18n("Unable to load game..."));

        return false;
    }
}
