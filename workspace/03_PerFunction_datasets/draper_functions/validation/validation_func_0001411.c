quoteString(string const & arg)
{
	string res;
	res += '"';
	res += subst(subst(arg, "\\", "\\\\"), "\"", "\\\"");
	res += '"';
	return res;
}
