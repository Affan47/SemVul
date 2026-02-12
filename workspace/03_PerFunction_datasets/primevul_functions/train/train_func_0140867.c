std::string get_user_data_dir()
{


	if (user_data_dir.empty())
	{
		set_user_data_dir(std::string());
	}
	return user_data_dir;
}
