append(QFile &file, const QString &type)
{
	bool isOpen = file.isOpen();
	if (isOpen || file.open(QIODevice::ReadOnly)) {
		QString cid = QString("sha1+%1@bob.xmpp.org").arg(
			QString(QCryptographicHash::hash(file.readAll(),
											QCryptographicHash::Sha1).toHex()));
		_localFiles[cid] = QPair<QString,QString>(file.fileName(), type);
		if (!isOpen) {
			file.close();
		}
		return cid;
	}
	return QString();
}
