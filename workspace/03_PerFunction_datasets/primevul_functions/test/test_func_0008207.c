static std::string getDescription(const std::string &fulltext, int line)
{
	if (line < 1) return "";

	unsigned int start = 0;
	for (; start<fulltext.length() ; ++start) {
		if (line <= 1) break;
		if (fulltext[start] == '\n') line--;
	}


	if (fulltext.compare(start, 2, "//") != 0) return "";


	start = start+2;


	while (fulltext[start] == ' ' || fulltext[start] == '\t') start++;
	std::string retString = "";


	while (fulltext[start] != '\n') {

		if (fulltext.compare(start, 2, "//") == 0) {
			retString += " ";
			start++;
		} else {
			retString += fulltext[start];
		}
		start++;
	}
	return retString;
}
