by_name (const string& str)
{
	Glib::Threads::RWLock::ReaderLock lm (registry_lock);

	for (Controllables::iterator i = registry.begin(); i != registry.end(); ++i) {
		if ((*i)->_name == str) {
			return (*i);
		}
	}
	return 0;
}
