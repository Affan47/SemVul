beginNamespace(std::ostream& ostr)
{
	std::string ns = _page.get("page.namespace", "");
	if (!ns.empty())
	{
		StringTokenizer tok(ns, ":", StringTokenizer::TOK_IGNORE_EMPTY | StringTokenizer::TOK_TRIM);
		for (StringTokenizer::Iterator it = tok.begin(); it != tok.end(); ++it)
		{
			ostr << "namespace " << *it << " {\n";
		}
		ostr << "\n\n";
	}
}
