mapPut(const QString &basename, const QVariant &key)
{
	QStringList children = getChildOptionNames( basename, true, true);
	foreach (QString path, children) {
		if (getOption(path+".key") == key) {
			return path;
		}
	}


	QString path;
	int i = 0;
	do {
		path = basename+".m"+QString::number(i);
		++i;
	} while (children.contains(path));
	setOption(path + ".key", key);
	return path;
}
