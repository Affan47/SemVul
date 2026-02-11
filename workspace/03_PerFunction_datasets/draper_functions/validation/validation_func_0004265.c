listdir(const std::string& dir, bool includeHidden) {
	std::vector<std::string> dirs;
	dirent* entry;
	DIR* dp = opendir(dir.c_str());
	if (dp == NULL)
		return dirs;
	while((entry = readdir(dp)))
		if(includeHidden || entry->d_name[0] != '.')
			dirs.push_back(entry->d_name);
	closedir(dp);
	std::sort(dirs.begin(),dirs.end());
	return dirs;
}
