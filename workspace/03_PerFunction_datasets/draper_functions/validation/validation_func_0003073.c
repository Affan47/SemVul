pasteRowOrCol(void)
{
	pf_Frag_Strux* cellSDH, *tableSDH;
	PT_DocPosition pos = m_pView->getPoint();
	if(m_iPrevSelectionMode == FV_SelectionMode_TableColumn)
	{


		getDoc()->beginUserAtomicGlob();


		m_pView->cmdInsertCol(m_pView->getPoint(),false);


		m_pView->_saveAndNotifyPieceTableChange();


		getDoc()->disableListUpdates();
		if (!m_pView->isSelectionEmpty())
		{
			m_pView->_clearSelection();
		}
		getDoc()->setDontImmediatelyLayout(true);
		pos = m_pView->getPoint();
		PT_DocPosition posTable,posCell;
		UT_sint32 iLeft,iRight,iTop,iBot;
		posCell = 0;
		m_pView->getCellParams(pos, &iLeft, &iRight,&iTop,&iBot);
		bool bRes = getDoc()->getStruxOfTypeFromPosition(pos,PTX_SectionCell,&cellSDH);
		bRes = getDoc()->getStruxOfTypeFromPosition(pos,PTX_SectionTable,&tableSDH);
		UT_return_if_fail(bRes);
		posTable = getDoc()->getStruxPosition(tableSDH) + 1;
		UT_sint32 numRows = 0;
		UT_sint32 numCols = 0;
		UT_sint32 i = 0;
		getDoc()-> getRowsColsFromTableSDH(tableSDH, m_pView->isShowRevisions(), m_pView->getRevisionLevel(),
										   &numRows, &numCols);

		PD_DocumentRange DocRange(getDoc(),posCell,posCell);
		for(i=0; i<getNumSelections();i++)
		{
			posCell = m_pView->findCellPosAt(posTable,i,iLeft)+2;
			m_pView->setPoint(posCell);
			PD_DocumentRange * pR = getNthSelection(i);
			if(pR->m_pos1 == pR->m_pos2)
			{


				continue;
			}
			UT_ByteBuf * pBuf = m_vecSelRTFBuffers.getNthItem(i);
			const unsigned char * pData = pBuf->getPointer(0);
			UT_uint32 iLen = pBuf->getLength();
			DocRange.m_pos1 = posCell;
			DocRange.m_pos2 = posCell;
			IE_Imp_RTF * pImpRTF = new IE_Imp_RTF(getDoc());
			pImpRTF->pasteFromBuffer(&DocRange,pData,iLen);
			DELETEP(pImpRTF);
			fl_SectionLayout * pSL = m_pView->getCurrentBlock()->getSectionLayout();
			pSL->checkAndAdjustCellSize();
		}
		getDoc()->endUserAtomicGlob();
		getDoc()->setDontImmediatelyLayout(false);
		m_pView->_generalUpdate();


		getDoc()->enableListUpdates();
		getDoc()->updateDirtyLists();


		m_pView->_restorePieceTableState();


		m_pView->notifyListeners(AV_CHG_MOTION);
		m_pView->_fixInsertionPointCoords();
		m_pView->_ensureInsertionPointOnScreen();

	}
	else
	{
	}
}
