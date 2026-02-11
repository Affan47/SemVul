gameActions (const int action)
{
   qDebug() << "GAME ACTION IS" << action;
   if ((m_activity != Idle) && (action != BUTTON) && (action != NEW)) {
      m_view->showPopup (i18n("Sorry, doing a move..."));
      return;
   }

   switch (action) {
   case NEW:
      newGame();
      break;
   case HINT:
      if (! isComputer (m_currentPlayer)) {
         KCubeWidget::enableClicks (false);
         computeMove();
      }
      break;
   case BUTTON:
      buttonClick();
      break;
   case UNDO:
      undo();
      break;
   case REDO:
      redo();
      break;
   case SAVE:
   case SAVE_AS:
      saveGame (action == SAVE_AS);
      break;
   case LOAD:
      loadGame();
      break;
   default:
      break;
   }
}
