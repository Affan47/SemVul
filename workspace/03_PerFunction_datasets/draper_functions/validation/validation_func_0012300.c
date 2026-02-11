enumerate(const std::string& key, Keys& range) const
{
	std::set<std::string> keys;
	for (ConfigList::const_iterator itc = _configs.begin(); itc != _configs.end(); ++itc)
	{
		Keys partRange;
		itc->pConfig->enumerate(key, partRange);
		for (Keys::const_iterator itr = partRange.begin(); itr != partRange.end(); ++itr)
		{
			if (keys.find(*itr) == keys.end())
			{
				range.push_back(*itr);
				keys.insert(*itr);
			}
		}
	}
}
