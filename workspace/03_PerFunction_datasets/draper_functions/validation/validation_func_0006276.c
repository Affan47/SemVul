findConnectorColor(const QStringList & names, QColor & color) {
	foreach (QString name, names) {
		RatsnestColor * ratsnestColor = m_allNames.value(name.toLower(), NULL);
		if (ratsnestColor == NULL) continue;

		color = ratsnestColor->m_ratsnest;
		return true;
	}

	return false;
}
