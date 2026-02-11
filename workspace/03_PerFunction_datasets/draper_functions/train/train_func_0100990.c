finished(int id, bool error)
{
	if (id != m_connectionId) {
		return;
	}

	if (error) {
		if (m_statusCode != 200) {
			DebugDialog::debug(QString("http check new version error %1").arg(m_http.errorString()));
			emit httpError(m_http.error());
			return;
		}
	}

	DebugDialog::debug("http check new version no error");
	emit releasesAvailable();
}
