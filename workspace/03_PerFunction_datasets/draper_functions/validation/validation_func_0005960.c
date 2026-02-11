tokenize(const std::string& delimiters)
{
	std::string::size_type lastPos = mLine.find_first_not_of(delimiters, 0);
	std::string::size_type pos     = mLine.find_first_of(delimiters, lastPos);
	mTokens.clear();
	mSize = 0;

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		if (pos == std::string::npos) pos = mLine.length() - lastPos;
		TokenPair newToken(lastPos, pos - lastPos);
		mTokens.push_back(newToken);
		mSize++;
		lastPos = mLine.find_first_not_of(delimiters, pos);
		pos = mLine.find_first_of(delimiters, lastPos);
		if (lastPos != std::string::npos && mLine[lastPos] == '#') break;
	}
}
