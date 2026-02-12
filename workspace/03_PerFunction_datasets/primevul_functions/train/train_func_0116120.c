static const std::string& get_version_path_suffix()
{
	static std::string suffix;


	if(suffix.empty()) {
		std::ostringstream s;
		s << game_config::wesnoth_version.major_version() << '.'
		  << game_config::wesnoth_version.minor_version();
		suffix = s.str();
	}

	return suffix;
}
