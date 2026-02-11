icompare(const std::string& str1, std::string::size_type pos1, std::string::size_type n, const std::string& str2, std::string::size_type pos2)
{
	std::string::size_type sz2 = str2.size();
	if (pos2 > sz2) pos2 = sz2;
	if (pos2 + n > sz2) n = sz2 - pos2;
	return icompare(str1, pos1, n, str2.begin() + pos2, str2.begin() + pos2 + n);
}
