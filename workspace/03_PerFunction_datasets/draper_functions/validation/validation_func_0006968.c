ReadNodeUrl(xmlNode* node, const char* attribute)
	{
		fm::string uriString = ReadNodeProperty(node, attribute);
		return FUUri(TO_FSTRING(uriString));
	}
