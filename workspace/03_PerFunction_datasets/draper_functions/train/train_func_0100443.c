toImage() const
	{
		return Image::constructor(QImage::fromData(mData), engine());
	}
