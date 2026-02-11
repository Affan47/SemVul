findModelPart(const QString & moduleID, long id) {
	if (m_root == NULL) return NULL;

	return findModelPartAux(m_root, moduleID, id);
}
