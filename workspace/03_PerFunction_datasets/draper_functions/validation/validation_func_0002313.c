entryPassive(const QString &serialized)
	{
		QMutexLocker locker(&ringMutex);

		QStringList parts = serialized.split(':');
		if(parts.count() < 2)
			return 0;
		if(unescape_string(parts[0]) != "qca-gnupg-1")
			return 0;

		QString entryId = unescape_string(parts[1]);
		if(entryId.isEmpty())
			return 0;

		PGPKey pub = getPubKey(entryId);
		if(pub.isNull())
			return 0;


		PGPKey sec = getSecKey(entryId, static_cast<MyPGPKeyContext *>(pub.context())->_props.userIds);

		MyKeyStoreEntry *c = new MyKeyStoreEntry(pub, sec, provider());
		c->_storeId = storeId(0);
		c->_storeName = name(0);
		return c;
	}
