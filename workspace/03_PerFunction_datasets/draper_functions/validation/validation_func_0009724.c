ekg2_dlopen(const char *name) {
#ifdef NO_POSIX_SYSTEM
	void *tmp = LoadLibraryA(name);
#else


	void *tmp = dlopen(name, RTLD_NOW | RTLD_GLOBAL);
#endif
	if (!tmp) {
		debug_warn("[plugin] could not be loaded: %s %s\n", name, dlerror());
	} else {
		debug_ok("[plugin] loaded: %s\n", name);
	}
	return tmp;
}
