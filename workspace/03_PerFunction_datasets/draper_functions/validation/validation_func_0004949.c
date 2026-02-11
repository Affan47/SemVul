set_component(int column, CL_Component *component)
{
	if(impl->items.size() <= (unsigned int)column)
	{
		for(unsigned int i = impl->items.size(); i <= (unsigned int)column; ++i)
			impl->items.push_back(CL_TreeItem_Generic::TreeItemStruct());
	}

	CL_TreeItem_Generic::TreeItemStruct item;
	item.component = component;
	impl->items[column] = item;
}
