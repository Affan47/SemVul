saveStateAndGeometry() {
	QSettings settings;
	settings.remove("bins2");
	settings.beginGroup("bins2");

	for(int j = m_stackTabWidget->count() - 1; j >= 0; j--) {
		PartsBinPaletteWidget *bin = qobject_cast<PartsBinPaletteWidget*>(m_stackTabWidget->widget(j));
		if (bin) {
			settings.beginGroup(QString::number(j));
			settings.setValue("location", BinLocation::toString(bin->location()));
			settings.setValue("title", bin->title());
			settings.setValue("path", bin->fileName());
			settings.endGroup();
		}
	}

	settings.endGroup();
}
