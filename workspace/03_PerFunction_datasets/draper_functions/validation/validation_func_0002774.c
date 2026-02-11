handleHighlight(const ConfigLine& configLine, QTextCursor& cursor, QTextCharFormat& format)
{
	if (configLine.inError())
		format.setForeground(Qt::red);
	else
		format.setForeground(Qt::black);
	cursor.setCharFormat(format);
	mFreeEdit->setTextCursor(cursor);
}
