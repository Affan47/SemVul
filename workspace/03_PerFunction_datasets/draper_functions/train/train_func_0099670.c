Contains(const char *charBytes, size_t len) const {
	PLATFORM_ASSERT(len <= 4);
	if (!startByteHasReprs[static_cast<unsigned char>(charBytes[0])])
		return false;
	MapRepresentation::const_iterator it = mapReprs.find(KeyFromString(charBytes, len));
	return it != mapReprs.end();
}
