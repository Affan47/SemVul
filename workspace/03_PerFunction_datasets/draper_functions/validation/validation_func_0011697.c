ksl_storeUpdated(int id)
	{
		KeyStoreListContext *c = (KeyStoreListContext *)sender();

		QCA_logTextMessage(QString("keystore: ksl_storeUpdated %1 %2").arg(c->provider()->name(), QString::number(id)), Logger::Information);

		QMutexLocker locker(&m);
		for(int n = 0; n < items.count(); ++n)
		{
			Item &i = items[n];
			if(i.owner == c && i.storeContextId == id)
			{
				++i.updateCount;

				QCA_logTextMessage(QString("keystore: %1 updateCount = %2").arg(i.name, QString::number(i.updateCount)), Logger::Information);

				QCA_logTextMessage(QString("keystore: emitting updated"), Logger::Information);
				emit updated_p();
				return;
			}
		}
	}
