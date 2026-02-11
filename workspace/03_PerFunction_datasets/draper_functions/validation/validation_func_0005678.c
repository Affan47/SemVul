sizeHint() const
{
	QFontMetrics m(font_);
	return QSize(m.width(text_) + 10, m.ascent() + m.descent() + 6);
}
