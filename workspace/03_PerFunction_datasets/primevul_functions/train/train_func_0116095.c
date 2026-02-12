const std::string& get_user_data_dir()
{


	if (user_data_dir.empty())
	{
		if (game_config::preferences_dir.empty())
			set_preferences_dir(std::string());
		else {
			user_data_dir = game_config::preferences_dir;
			setup_user_data_dir();
		}
	}
	return user_data_dir;
}
