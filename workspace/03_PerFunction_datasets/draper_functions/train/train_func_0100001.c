writeElement(const wchar_t* name, bool empty,
				  core::array<core::stringw> &names,
				  core::array<core::stringw> &values)
{
	if (!File || !name)
		return;

	if (Tabs > 0)
	{
		for (int i=0; i<Tabs; ++i)
			File->write(L"\t", sizeof(wchar_t));
	}


	File->write(L"<", sizeof(wchar_t));
	File->write(name, wcslen(name)*sizeof(wchar_t));


	u32 i=0;
	for (; i < names.size() && i < values.size(); ++i)
		writeAttribute(names[i].c_str(), values[i].c_str());


	if (empty)
		File->write(L" />", 3*sizeof(wchar_t));
	else
	{
		File->write(L">", sizeof(wchar_t));
		++Tabs;
	}

	TextWrittenLast = false;
}
