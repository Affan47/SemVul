disconnect(void) {
	if (!isConnected())
		return true;

	ArLog::log(ArLog::Normal, "%s: Disconnecting", getName());

	laserDisconnectNormally();
	return true;
}
