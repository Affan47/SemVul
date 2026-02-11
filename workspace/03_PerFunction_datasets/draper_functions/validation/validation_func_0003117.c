Arc(GB_PAINT *d, float xc, float yc, float radius, float angle, float length)
{
	CREATE_PATH(d);

	QRectF rect;
	rect.setCoords((qreal)(xc - radius), (qreal)(yc - radius), (qreal)(xc + radius), (qreal)(yc + radius));

	angle = - angle;
	length = - length;

	PATH(d)->arcMoveTo(rect, to_deg(angle));
	PATH(d)->arcTo(rect, to_deg(angle), to_deg(length));
}
