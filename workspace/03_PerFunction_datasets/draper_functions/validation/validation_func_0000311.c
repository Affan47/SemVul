setUpColor(ConnectorItem * fromConnectorItem, ConnectorItem * toConnectorItem, Wire * wire, QUndoCommand * parentCommand) {

		QString tc = traceColor(fromConnectorItem);
		new WireColorChangeCommand(this, wire->id(), tc, tc, 1.0, 1.0, parentCommand);
		double traceWidth = getTraceWidth();
		if (autorouteTypePCB()) {
			double minDim = qMin(fromConnectorItem->minDimension(), toConnectorItem->minDimension());
			if (minDim < traceWidth) {
				traceWidth = getSmallerTraceWidth(minDim);
			}
		}
		new WireWidthChangeCommand(this, wire->id(), traceWidth, traceWidth, parentCommand);

}
