dispatch(const Socket& socket, SocketNotification* pNotification)
{
	NotifierPtr pNotifier;
	{
		FastMutex::ScopedLock lock(_mutex);
		EventHandlerMap::iterator it = _handlers.find(socket);
		if (it != _handlers.end())
			pNotifier = it->second;
		else
			return;
	}
	dispatch(pNotifier, pNotification);
}
