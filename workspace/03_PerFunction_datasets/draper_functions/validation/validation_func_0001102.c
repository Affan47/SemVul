convert_string_char(const string & src)
    {
	basic_string<my_char> ret;

	string::const_iterator ut = src.begin();
	while(ut != src.end())
	{
	    ret += my_char(*ut);
	    ++ut;
	}

	return ret;
    }
