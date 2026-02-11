nextToken(const QStringRef& previous, bool untilEnd)
{
	const QString* str = previous.string();
	if (str == 0)
		return QStringRef();

	int i;
	int start = -1;
	int firstPos = previous.position() + previous.size();

	for (i = firstPos; i < str->size(); i++)
	{
		if (str->at(i).isSpace())
		{
			if (start == -1)
				continue;
			break;
		}
		else if (start == -1)
		{
			start = i;
			if (untilEnd)
			{
				int end = str->size();
				while (str->at(--end).isSpace())
					;
				i = end + 1;
				break;
			}
		}
	}

	if (start == -1)
		return QStringRef();
	return QStringRef(str, start, i - start);
}
