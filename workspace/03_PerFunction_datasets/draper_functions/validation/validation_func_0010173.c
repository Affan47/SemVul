currentItem(QString const & type,
	QModelIndex const & index) const
{
	const_iterator it = models_.find(type);
	if (it == models_.end() || !index.isValid()) {
		LYXERR(Debug::GUI, "TocModels::currentItem(): QModelIndex is invalid!");
		return TocItem();
	}
	LASSERT(index.model() == it.value()->model(), return TocItem());

	return it.value()->tocItem(index);
}
