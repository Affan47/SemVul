scripting_GetGlobal(const char *global, const char *s, ...) {
	lua_getglobal(L, global);
	if(s) {
		va_list ap;
		va_start(ap, s);
		getGlobal(s, ap);
		va_end(ap);
	}
	return 0;
}
