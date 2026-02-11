regexMatch(const String &aRegEx, Container *resultStrings) const
{
	const char *re = aRegEx.toString();
	bool result = false;
	regex_t rx;

	int r = regcomp(&rx, re, REG_EXTENDED | ((compareChar('A','a')==0) ? REG_ICASE : 0));
	if (r) throw MsgException("EINVAL");

	regmatch_t pmatch[MAX_REGEX_MATCHES];
	if (regexec(&rx, (char*)mContent, MAX_REGEX_MATCHES, pmatch, 0) != 0) return false;

	if (resultStrings) {
		for (int i=1; i<MAX_REGEX_MATCHES; i++) {
			if (pmatch[i].rm_so == -1) break;
			String *s = new String();
			subString(pmatch[i].rm_so, pmatch[i].rm_eo-pmatch[i].rm_so, *s);
			resultStrings->insert(s);
		}
	}

	delete re;
	return result;
}
