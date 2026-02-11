updateConnections(bool includeRatsnest, QList<ConnectorItem *> & already) {
	updateConnectionsAux(includeRatsnest, already);
	foreach (ItemBase * lkpi, m_layerKin) {
		lkpi->updateConnectionsAux(includeRatsnest, already);
	}
}
