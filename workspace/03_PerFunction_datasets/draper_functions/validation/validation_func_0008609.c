CPICTURE_create(const QPixmap *pixmap)
{
	CPICTURE *pict = create();
	if (pixmap) *pict->pixmap = *pixmap;
	return pict;
}
