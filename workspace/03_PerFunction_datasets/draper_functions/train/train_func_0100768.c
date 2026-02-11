getPinLabels(bool & hasLocal) {
	hasLocal = false;
	QStringList labels;
	QList<Connector *> sortedConnectors = sortConnectors();
	if (sortedConnectors.count() == 0) return labels;

	foreach (Connector * connector, sortedConnectors) {
		labels.append(connector->connectorSharedName());
		if (!connector->connectorLocalName().isEmpty()) {
			hasLocal = true;
		}
	}

	return labels;
}
