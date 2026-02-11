reduceChat()
{
  kDebug();
  m_chatIsReduced = true;

  m_lastWidthChat = m_bottomDock->width();


  QPixmap upChatReducePix(m_dirs->findResource("appdata", m_automaton->skin() + "/Images/upArrow.png"));
  m_reduceChatButton->setIcon(upChatReducePix);
  m_chatDlg->hide();
  m_titleChatMsg->show();
}
