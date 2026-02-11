initFilesToLoad()
{
	for (int i = 1; i < m_arguments.length(); i++) {
		QFileInfo fileinfo(m_arguments[i]);
		if (fileinfo.exists() && !fileinfo.isDir()) {
			m_filesToLoad << m_arguments[i];
		}
	}
}
