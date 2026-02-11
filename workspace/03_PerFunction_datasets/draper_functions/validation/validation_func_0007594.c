inactivateConnectors() {

	foreach (ConnectorItem * item, cachedConnectorItems()) {
		item->setInactive(true);
	}
}
