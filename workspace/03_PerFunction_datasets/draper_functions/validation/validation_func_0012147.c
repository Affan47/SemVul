add(FileName const & file)
{

	LastFiles::iterator it = find(lastfiles.begin(), lastfiles.end(), file);
	if (it != lastfiles.end())
		lastfiles.erase(it);
	lastfiles.insert(lastfiles.begin(), file);
	if (lastfiles.size() > num_lastfiles)
		lastfiles.pop_back();
}
