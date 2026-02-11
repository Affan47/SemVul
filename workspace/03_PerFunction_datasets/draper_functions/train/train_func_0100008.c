encode(const std::string& str, const std::string& reserved, std::string& encodedStr)
{
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		char c = *it;
		if ((c >= 'a' && c <= 'z') ||
		    (c >= 'A' && c <= 'Z') ||
		    (c >= '0' && c <= '9') ||
		    c == '-' || c == '_' ||
		    c == '.' || c == '~')
		{
			encodedStr += c;
		}
		else if (c <= 0x20 || c >= 0x7F || ILLEGAL.find(c) != std::string::npos || reserved.find(c) != std::string::npos)
		{
			encodedStr += '%';
			encodedStr += NumberFormatter::formatHex((unsigned) (unsigned char) c, 2);
		}
		else encodedStr += c;
	}
}
