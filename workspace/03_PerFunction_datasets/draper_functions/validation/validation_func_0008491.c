collectFemaleConnectees(QSet<ItemBase *> & items) {
	bool hasMale = false;
	foreach (ConnectorItem * item, cachedConnectorItems()) {
		if (item->connectorType() == Connector::Male) {
			hasMale = true;
			continue;
		}

		if (item->connectorType() != Connector::Female) continue;

		foreach (ConnectorItem * toConnectorItem, item->connectedToItems()) {
			if (toConnectorItem->attachedToItemType() == ModelPart::Wire) continue;
			if (!toConnectorItem->attachedTo()->isVisible()) continue;

			items.insert(toConnectorItem->attachedTo());
		}
	}

	return hasMale;
}
