closeAllFileDescriptors(int lastToKeepOpen) {
	#if defined(F_CLOSEM)
		int ret;
		do {
			ret = fcntl(lastToKeepOpen + 1, F_CLOSEM);
		} while (ret == -1 && errno == EINTR);
		if (ret != -1) {
			return;
		}
	#elif defined(HAS_CLOSEFROM)
		closefrom(lastToKeepOpen + 1);
		return;
	#endif

	for (int i = getHighestFileDescriptor(); i > lastToKeepOpen; i--) {


		int ret;
		do {
			ret = close(i);
		} while (ret == -1 && errno == EINTR);
	}
}
