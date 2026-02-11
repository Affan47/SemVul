unescape_config_stringlist(const QString &in, QStringList *_out)
{
	QStringList out;
	QStringList list = in.split(',');
	for(int n = 0; n < list.count(); ++n)
	{
		QString str;
		if(!unescape_string(list[n], &str))
			return false;
		out += str.trimmed();
	}
	*_out = out;
	return true;
}
