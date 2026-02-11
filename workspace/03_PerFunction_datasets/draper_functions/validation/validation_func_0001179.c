writeConfig(const QString &name, const QVariantMap &config, bool systemWide = false)
{
	QSettings settings(QSettings::NativeFormat, systemWide ? QSettings::SystemScope : QSettings::UserScope, "Affinix", "QCA2");
	settings.beginGroup("ProviderConfig");


	settings.setValue("version", 2);


	QStringList providerNames = settings.value("providerNames").toStringList();
	if(!providerNames.contains(name))
		providerNames += name;
	settings.setValue("providerNames", providerNames);

	settings.beginGroup(name);
	QMapIterator<QString,QVariant> it(config);
	while(it.hasNext())
	{
		it.next();
		settings.setValue(it.key(), it.value());
	}
	settings.endGroup();

	if(settings.status() == QSettings::NoError)
		return true;
	return false;
}
