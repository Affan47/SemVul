applySettings(ConnectionsModel* pConnectionsModel, ConnectionSettings* pConnectionSettings, const QString strMsgBoxTitle, QWidget* pFocus)
{
   const OpenSSLSettings openSSLSettings(Preferences().openSSLSettings());
   const int iConnections(pConnectionSettings->connections());

   bool fRet(true);

   if (iConnections > 0)
   {
      if (pConnectionsModel->isWriteable())
      {
         if (pFocus)
            QMessageBox::information(NULL, strMsgBoxTitle, tr("You need to reconnect for your changes to take effect!"));

         fRet = ConfWriter::write(ConfWriter::IPsec);
         if (fRet) fRet = ConfWriter::write(ConfWriter::IPsecSECRET);
         if (fRet) fRet = ConfWriter::write(ConfWriter::L2TP);

         for (int i = 0; fRet && i < iConnections; i++)
         {
            const QString strConnectionName(pConnectionSettings->connection(i));

            fRet = ConfWriter::write(ConfWriter::PPP, strConnectionName);
            if (fRet)
            {
               const QString strDNSConfInstance(QCoreApplication::instance()->objectName() + "-" +strConnectionName);
               const QString strDNSConfFile(ConfWriter::fileName(ConfWriter::PPPDNSCONF, strDNSConfInstance));
               const PppIpSettings ipSettings(pConnectionSettings->pppSettings(strConnectionName).ipSettings());

               if (ipSettings.usePeerDns() || (ipSettings.alternateDnsServerAddress().isEmpty() && ipSettings.preferredDnsServerAddress().isEmpty() && ipSettings.searchDomains().isEmpty()))
               {
                  if (QFile::exists(strDNSConfFile))
                     QFile::remove(strDNSConfFile);
               }
               else
                  fRet = ConfWriter::write(ConfWriter::PPPDNSCONF, strDNSConfInstance);
            }
         }

         if (fRet) fRet = ConfWriter::write(ConfWriter::PPPUPSCRIPT);
         if (fRet) fRet = ConfWriter::write(ConfWriter::PPPDOWNSCRIPT);
         if (fRet) fRet = ConfWriter::write(ConfWriter::GETIPSECINFO);
         if (fRet) fRet = ConfWriter::write(ConfWriter::RSYSLOG);
         if (fRet)
         {
            if (openSSLSettings.enginePath().isEmpty() || openSSLSettings.pkcs11Path().isEmpty() || openSSLSettings.engineId().isEmpty())
            {
               const QString strOpenSSLConfFile(ConfWriter::fileName(ConfWriter::OPENSSL));
               if (QFile::exists(strOpenSSLConfFile))
                  QFile::remove(strOpenSSLConfFile);
            }
            else
               fRet = ConfWriter::write(ConfWriter::OPENSSL);
         }
      }
      else
      {
         if (pFocus)
            QMessageBox::critical(NULL, tr("Apply settings"), tr("You do not have the permission to apply settings"));

         fRet = false;
      }
   }

   if (pFocus)
      pFocus->setFocus();

    return(fRet);
}
