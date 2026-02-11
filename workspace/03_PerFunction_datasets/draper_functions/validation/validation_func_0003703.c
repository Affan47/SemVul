encodePassword(const QString &pass, const QString &key)
{
	QString result;
	int n1, n2;

	if(key.length() == 0)
		return pass;

	for(n1 = 0, n2 = 0; n1 < pass.length(); ++n1) {
		ushort x = pass.at(n1).unicode() ^ key.at(n2++).unicode();
		QString hex;
		hex.sprintf("%04x", x);
		result += hex;
		if(n2 >= key.length())
			n2 = 0;
	}
	return result;
}
