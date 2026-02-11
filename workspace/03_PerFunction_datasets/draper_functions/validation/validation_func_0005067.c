eventOpen ()
{
	UT_VECTOR_PURGEALL(UT_UTF8String*, m_vecFields);
	m_vecFields.clear();

	UT_return_if_fail(m_pFrame);
	m_pFrame->raise();
	XAP_Dialog_Id id = XAP_DIALOG_ID_FILE_OPEN;

	XAP_DialogFactory * pDialogFactory
		= static_cast<XAP_DialogFactory *>(m_pFrame->getDialogFactory());

	XAP_Dialog_FileOpenSaveAs * pDialog
		= static_cast<XAP_Dialog_FileOpenSaveAs *>(pDialogFactory->requestDialog(id));
	UT_return_if_fail (pDialog);

	UT_uint32 filterCount = 0;

	filterCount = IE_MailMerge::getMergerCount();

	const char ** szDescList = static_cast<const char **>(UT_calloc(filterCount + 1, sizeof(char *)));
	const char ** szSuffixList = static_cast<const char **>(UT_calloc(filterCount + 1, sizeof(char *)));
	IEMergeType * nTypeList = static_cast<IEMergeType *>(UT_calloc(filterCount + 1, sizeof(IEMergeType)));
	UT_uint32 k = 0;

	while (IE_MailMerge::enumerateDlgLabels(k, &szDescList[k], &szSuffixList[k], &nTypeList[k]))
		k++;

	pDialog->setFileTypeList(szDescList, szSuffixList, static_cast<const UT_sint32 *>(nTypeList));

	pDialog->setDefaultFileType(IE_MailMerge::fileTypeForSuffix (".xml"));

	pDialog->runModal(m_pFrame);

	XAP_Dialog_FileOpenSaveAs::tAnswer ans = pDialog->getAnswer();
	bool bOK = (ans == XAP_Dialog_FileOpenSaveAs::a_OK);

	if (bOK)
    {
		UT_UTF8String filename (pDialog->getPathname());
		UT_sint32 type = pDialog->getFileType();

		IE_MailMerge * pie = NULL;
		UT_Error errorCode = IE_MailMerge::constructMerger(filename.utf8_str(), static_cast<IEMergeType>(type), &pie);
		if (!errorCode && pie)
		{
			pie->getHeaders (filename.utf8_str(), m_vecFields);
			DELETEP(pie);
		}
	}

	pDialogFactory->releaseDialog(pDialog);

	setFieldList();
}
