parseSoftware(const QByteArray &val, QString *str)
{
	*str = QString::fromUtf8(val);
	return true;
}
