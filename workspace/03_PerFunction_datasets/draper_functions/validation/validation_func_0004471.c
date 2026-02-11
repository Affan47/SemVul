getCookies(NameValueCollection& cookies) const
{
	NameValueCollection::ConstIterator it = find(COOKIE);
	while (it != end() && Poco::icompare(it->first, COOKIE) == 0)
	{
		splitParameters(it->second.begin(), it->second.end(), cookies);
		++it;
	}
}
