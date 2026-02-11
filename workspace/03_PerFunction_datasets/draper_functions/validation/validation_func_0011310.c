get_item(int index) const
{
	int pos = 0;
	std::vector<CL_ListItem *>::const_iterator it;
	for(it = items.begin(); it != items.end(); it++, pos++)
		if(pos == index)
			return (*it);

	return 0;
}
