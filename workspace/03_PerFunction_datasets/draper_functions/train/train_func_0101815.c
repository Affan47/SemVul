writeSettings() const
{
   const ConnectionSettings settings;
   const PppSettings pppSettings = settings.pppSettings(m_strConnectionName);

   bool fRet = pppSettings.setRemoteName(m_Widget.m_pRemoteNameEdit->text());

   return(fRet);
}
