AddItem(bool fFatal, int nID, GdlObject * pgdlObj, const GrpLineAndFile * plnf,
	std::string staMsg)
{
	GrpLineAndFile lnf(0, 0, "");
	if (plnf == NULL)
	{
		if (pgdlObj)
			lnf = pgdlObj->LineAndFile();
	}
	else
		lnf = *plnf;

	GrcErrorItem * perr = new GrcErrorItem(fFatal, nID, lnf, staMsg, pgdlObj);
	m_vperr.push_back(perr);

	if (fFatal)
		m_fFatalError = true;
}
