main()
{
	string s = "this is something";
	for (auto it = s.begin(); it != s.end(); ++it) {
		if (!isspace(*it))
			*it = toupper(*it);
	}

	cout << s << endl;
	return 0;
}
