buildrawtext(std::string& value)
{
	while (char c = safeget())
	{
		switch (c) {
		case '$':
		case '@':
		case '\\':
		case '{':
		case '}':
		case '\r':
		case '\n':
		case ' ':
		case '\t':
			safeunget();
			return;
		default:
			value+= c;
		}
	}
}
