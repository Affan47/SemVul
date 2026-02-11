boundingRect() const
{
	if (m_legPolygon.count() < 2) return NonConnectorItem::boundingRect();

	return shape().controlPointRect();
}
