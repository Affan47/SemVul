ParseAsZVM(CLine* pLine, CDirentry &entry)
{
	int index = 0;
	CToken token;


	if (!pLine->GetToken(index, token))
		return false;

	entry.name = token.GetString();


	if (!pLine->GetToken(++index, token))
		return false;
	entry.name += _T(".") + token.GetString();


	if (!pLine->GetToken(++index, token))
		return false;
	wxString format = token.GetString();
	if (format != _T("V") && format != _T("F"))
		return false;


	if (!pLine->GetToken(++index, token))
		return false;

	if (!token.IsNumeric())
		return false;

	entry.size = token.GetNumber();


	if (!pLine->GetToken(++index, token))
		return false;

	if (!token.IsNumeric())
		return false;

	entry.size *= token.GetNumber();


	if (!pLine->GetToken(++index, token))
		return false;

	if (!token.IsNumeric())
		return false;

	entry.flags = 0;


	if (!pLine->GetToken(++index, token))
		return false;

	if (!ParseShortDate(token, entry, true))
		return false;


	if (!pLine->GetToken(++index, token))
		return false;

	if (!ParseTime(token, entry))
		return false;


	if (!pLine->GetToken(++index, token))
		return false;

	entry.ownerGroup = token.GetString();


	if (pLine->GetToken(++index, token))
		return false;

	entry.permissions = _T("");
	entry.target = _T("");

	if (entry.has_time())
		entry.time.Add(m_timezoneOffset);

	return true;
}
