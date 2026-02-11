polygonFromElement(QDomElement & element)
{
	QPolygonF poly;
	QDomElement point = element.firstChildElement("point");
	while (!point.isNull()) {
		double x = point.attribute("x").toDouble();
		double y = point.attribute("y").toDouble();
		poly.append(QPointF(x, y));
		point = point.nextSiblingElement("point");
	}
	return poly;
}
