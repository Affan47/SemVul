save(const QString& filename)
{
	QFile file(filename);
	if(!file.open(QFile::WriteOnly))
		return false;

	QTextStream ts(&file);

	foreach(PdnGame* game, m_database) {
		ts << game->toString() << endl << endl;
	}

	file.close();
	return true;
}
