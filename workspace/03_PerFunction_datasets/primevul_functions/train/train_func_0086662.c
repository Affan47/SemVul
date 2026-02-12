int DNS::ClearCache()
{

	int rv = this->cache->size();
	delete this->cache;
	this->cache = new dnscache();
	return rv;
}
