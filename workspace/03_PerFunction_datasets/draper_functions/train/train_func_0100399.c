get_new4old(const char* oldname, int tshift) const
{
	Toldnamemap::const_iterator it = old2new.find(oldname);
	if (it != old2new.end()) {
		const Tshiftnameset& sset = (*it).second;
		for (Tshiftnameset::const_iterator itt = sset.begin();
			 itt != sset.end(); ++itt)
			if ((*itt).second == - tshift)
				return (*itt).first;
	}
	return NULL;
}
