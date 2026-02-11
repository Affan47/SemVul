operator()(messageId id, time_t t, size_t s)
{
	if (*id.c_str() == 0)
		return *this;

	map<messageId, WatchInfo>::iterator p=watchList.find(id);

	if (p == watchList.end())
		p=watchList.insert(make_pair(id, WatchInfo(t, s))).first;

	p->second=WatchInfo(t, s);

	return *this;
}
