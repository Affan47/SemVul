formatOption(std::ostream& ostr, const Option& option, int width) const
{
	int shortLen = (int) option.shortName().length();
	int fullLen  = (int) option.fullName().length();

	int n = 0;
	if (_unixStyle && shortLen > 0)
	{
		ostr << shortPrefix() << option.shortName();
		n += (int) shortPrefix().length() + (int) option.shortName().length();
		if (option.takesArgument())
		{
			if (!option.argumentRequired()) { ostr << '['; ++n; }
			ostr << option.argumentName();
			n += (int) option.argumentName().length();
			if (!option.argumentRequired()) { ostr << ']'; ++n; }
		}
		if (fullLen > 0) { ostr << ", "; n += 2; }
	}
	if (fullLen > 0)
	{
		ostr << longPrefix() << option.fullName();
		n += (int) longPrefix().length() + (int) option.fullName().length();
		if (option.takesArgument())
		{
			if (!option.argumentRequired()) { ostr << '['; ++n; }
			ostr << '=';
			++n;
			ostr << option.argumentName();
			n += (int) option.argumentName().length();
			if (!option.argumentRequired()) { ostr << ']'; ++n; }
		}
	}
	while (n < width) { ostr << ' '; ++n; }
}
