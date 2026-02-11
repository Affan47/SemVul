tracker_updated()
	{
		QMutexLocker locker(&m);
		if(!pending)
		{
			QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
			pending = true;
		}
	}
