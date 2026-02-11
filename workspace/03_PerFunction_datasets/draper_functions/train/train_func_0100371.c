getItemPointerByUid(const QString &uid) const {

	foreach (CalendarItem *item, m_sortedByBeginList)
		if (item->uid() == uid)
			return item;
	return 0;
}
