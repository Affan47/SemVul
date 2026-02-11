methodToString(int method)
{
	for(int n = 0; method_table[n].str; ++n)
	{
		if(method_table[n].method == (Method)method)
			return QString::fromLatin1(method_table[n].str);
	}

	return QString();
}
