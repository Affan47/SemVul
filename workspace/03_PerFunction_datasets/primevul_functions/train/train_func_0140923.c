std::string get_binary_file_location(const std::string& type, const std::string& filename)
{


	for(std::string::size_type pos = filename.rfind("../"); pos != std::string::npos;)
		return get_binary_file_location(type, filename.substr(pos + 3));

	if (!is_legal_file(filename))
		return std::string();

	BOOST_FOREACH(const std::string &bp, get_binary_paths(type))
	{
		path bpath(bp);
		bpath /= filename;
		DBG_FS << "  checking '" << bp << "'\n";
		if (file_exists(bpath)) {
			DBG_FS << "  found at '" << bpath.string() << "'\n";
			return bpath.string();
		}
	}

	DBG_FS << "  not found\n";
	return std::string();
}
