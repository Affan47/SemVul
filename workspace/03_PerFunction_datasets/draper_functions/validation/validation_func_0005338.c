getNextWord(const string &line, size_t currPos) const
{
	size_t lineLength = line.length();

	if (currPos == lineLength - 1)
		return string();

	size_t start = line.find_first_not_of(" \t", currPos + 1);
	if (start == string::npos || !isLegalNameChar(line[start]))
		return string();

	size_t end;
	for (end = start + 1; end <= lineLength; end++)
	{
		if (!isLegalNameChar(line[end]) || line[end] == '.')
			break;
	}

	return line.substr(start, end - start);
}
