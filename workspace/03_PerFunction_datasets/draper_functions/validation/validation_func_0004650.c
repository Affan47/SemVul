doReadItemList(const char* filename, ListContainer* lc, const char* fname, bool swsort) {
	bool result = lc->readItemList(filename, false, 0);
	if (!result) {
		if (!is_daemonised) {
			std::cerr << "Error opening " << fname << std::endl;
		}
		syslog(LOG_ERR, "Error opening %s", fname);
		return false;
	}
	if (swsort)
		lc->doSort(true);
	else
		lc->doSort(false);
	return true;
}
