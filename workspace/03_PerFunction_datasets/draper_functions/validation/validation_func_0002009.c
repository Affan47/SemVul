updateModel()
{
	QFontDatabase database;
	QStringList fonts = database.families(m_system);
	fonts.sort();
	m_font_model->setStringList(fonts);
}
