recalculateHeights()
{
	TotalItemHeight = 0;
	IGUISkin* skin = Environment->getSkin();
	if (Font != skin->getFont())
	{
		if (Font)
			Font->drop();

		Font = skin->getFont();

		ItemHeight = 0;

		if(Font)
		{
			ItemHeight = Font->getDimension(L"A").Height + (CellHeightPadding * 2);
			Font->grab();
		}
	}
	TotalItemHeight = ItemHeight * Rows.size();
	checkScrollbars();
}
