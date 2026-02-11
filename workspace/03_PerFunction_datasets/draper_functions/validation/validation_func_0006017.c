onConnectionRemoved(const QString& strName)
{


   if (m_pTrayIconMenu && m_pActions)
   {
      QAction* pAction = NULL;
      for (int i = QUIT + 1; !pAction && i < m_pActions->size(); i++)
      {
         if (m_pActions->at(i)->text() == strName)
            pAction = m_pActions->at(i);
      }

      if (pAction)
      {
         m_pTrayIconMenu->removeAction(pAction);
         m_pActions->removeAll(pAction);
         delete pAction;
      }
   }


}
