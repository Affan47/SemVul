getRaw(const std::string& key, std::string& value) const
{
	std::string translatedKey = translateKey(key);
	return _pConfig->getRaw(translatedKey, value);
}
