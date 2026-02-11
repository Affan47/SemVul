setFilter(const QString& filter)
{
	m_filter_model->setFilterFixedString(filter);
	if (filter.isEmpty()) {
		m_scenes->setDragEnabled(true);
		m_scenes->setSelectionMode(QAbstractItemView::ExtendedSelection);
	} else {
		m_scenes->setDragEnabled(false);
		m_scenes->setSelectionMode(QAbstractItemView::SingleSelection);
	}
}
