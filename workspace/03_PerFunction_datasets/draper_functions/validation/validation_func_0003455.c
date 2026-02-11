Set(const char *key, const char *val, int lenKey, int lenVal) {
	mapss *props = static_cast<mapss *>(impl);
	if (!*key)
		return;
	if (lenKey == -1)
		lenKey = static_cast<int>(strlen(key));
	if (lenVal == -1)
		lenVal = static_cast<int>(strlen(val));
	(*props)[std::string(key, lenKey)] = std::string(val, lenVal);
}
