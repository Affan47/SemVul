findReplace(bool& bDoneEntireDocument)
{
	UT_ASSERT(m_sFind && m_sReplace);

	UT_uint32* pPrefix = _computeFindPrefix(m_sFind);
	bool bRes = _findReplace(pPrefix, bDoneEntireDocument, false );
	FREEP(pPrefix);

	updateScreen();

	if (isSelectionEmpty())
	{
		_updateInsertionPoint();
	}
	else
	{
		_ensureInsertionPointOnScreen();
		_drawSelection();
	}

	return bRes;
}
