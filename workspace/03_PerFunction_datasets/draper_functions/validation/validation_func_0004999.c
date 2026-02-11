List(CServerPath path , wxString subDir , int flags )
{
	LogMessage(Status, _("Retrieving directory listing..."));

	if (m_pCurOpData)
	{
		LogMessage(__TFILE__, __LINE__, this, Debug_Info, _T("List called from other command"));
	}
	CFtpListOpData *pData = new CFtpListOpData;
	pData->pNextOpData = m_pCurOpData;
	m_pCurOpData = pData;

	pData->opState = list_waitcwd;

	if (path.GetType() == DEFAULT)
		path.SetType(m_pCurrentServer->GetType());
	pData->path = path;
	pData->subDir = subDir;
	pData->refresh = (flags & LIST_FLAG_REFRESH) != 0;
	pData->fallback_to_current = !path.IsEmpty() && (flags & LIST_FLAG_FALLBACK_CURRENT) != 0;

	int res = ChangeDir(path, subDir, (flags & LIST_FLAG_LINK) != 0);
	if (res != FZ_REPLY_OK)
		return res;

	return ParseSubcommandResult(FZ_REPLY_OK);
}
