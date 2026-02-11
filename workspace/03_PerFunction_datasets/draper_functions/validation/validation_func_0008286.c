widgets() const
{
	QList<QWidget*> widgetList;
	QLinkedList<StackPage*>::ConstIterator itr;

	for (itr = pageList_.begin(); itr != pageList_.end(); ++itr)
		widgetList.append((*itr)->widget());

	return widgetList;
}
