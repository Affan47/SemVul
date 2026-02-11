is_coded_string(const std::string&s, std::string& name, int* mark_level)
{


	if (s.size() < 33) {
		return false;
	}
	char cname[100];
	int ml = 0;
	if (2 != sscanf(s.c_str(), AMPERSAND_CODING, cname, &ml)) {

		return false;
	}
	name.assign(cname);
	*mark_level = ml;

	return true;
}
