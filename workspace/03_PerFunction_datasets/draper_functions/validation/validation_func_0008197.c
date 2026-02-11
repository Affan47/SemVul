AddCategory(const wxTreeItemId& parent, wxString title, long ID, bool editNow)

{
	wxTreeItemId newCategoryID = InsertItem(parent, GetLastChild(parent), title, 1, -1,
            new SnippetItemData(SnippetItemData::TYPE_CATEGORY, ID));


	SortChildren(parent);

	if (editNow)
	{

		EnsureVisible(newCategoryID);
		EditLabel(newCategoryID);
        SetFileChanged(true);
	}

	return newCategoryID;
}
