extractLine(QByteArray *buf, bool *found)
{

	int index = buf->indexOf ("\r\n");
	if (index == -1) {

		if (found)
			*found = false;
		return "";
	}
	else {

		QString s = QString::fromAscii(buf->left(index));
		buf->remove(0, index + 2);

		if (found)
			*found = true;
		return s;
	}
}
