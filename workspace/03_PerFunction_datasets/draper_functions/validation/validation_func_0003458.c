initLegInfoAux(QDomElement & element, ConnectorInfo * connectorInfo)
{
	bool ok;
	double sw = element.attribute("stroke-width").toDouble(&ok);
	if (!ok) return false;

	double x1 = element.attribute("x1").toDouble(&ok);
	if (!ok) return false;

	double y1 = element.attribute("y1").toDouble(&ok);
	if (!ok) return false;

	double x2 = element.attribute("x2").toDouble(&ok);
	if (!ok) return false;

	double y2 = element.attribute("y2").toDouble(&ok);
	if (!ok) return false;

	connectorInfo->legStrokeWidth = sw;
	connectorInfo->legLine = QLineF(x1, y1, x2, y2);
	return true;
}
