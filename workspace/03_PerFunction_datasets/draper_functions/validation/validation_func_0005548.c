printInfo() const
{
	FileStream<std::ifstream> f(mLog);
	string buf;
	bool printed(false);

	string line(mName.size() + 2, '-');
	cout << line << "\n " << mName << " \n" << line << "\n" << endl;

	while (getline(f, buf) && buf[0] == '#') {
		if (buf == "#:Description")
			cout << "Description:\n" << endl;
		else if (!buf.find("#:")) {
			cutPrint(buf.substr(2));
			printed = true;
		}
	}

	if (printed)
		cout << endl;
}
