queueAll(UT_uint32 iReason)
{
	fl_DocSectionLayout * pSL = getFirstSection();
	if(pSL)
	{


		FV_View * pView = getView();
		UT_GenericVector<fl_BlockLayout*> vBL;
		const UT_sint32 iLimit = 5;

		fl_BlockLayout * pCurBL = pView->getBlockAtPosition(pView->getPoint());

		if(pCurBL)
		{
			fl_BlockLayout * pBL = pCurBL;

			UT_sint32 i = 0;
			for(i = 0; i < iLimit/2 + iLimit%2 && pBL; ++i, pBL = pBL->getPrevBlockInDocument())
			{
				vBL.addItem(pBL);
			}

			pBL = pCurBL->getNextBlockInDocument();
			for(i = iLimit/2 + iLimit%2; i < iLimit && pBL; ++i, pBL = pBL->getNextBlockInDocument())
			{
				vBL.addItem(pBL);
			}
		}

		fl_ContainerLayout* b = pSL->getFirstLayout();
		while (b)
		{


			if(b->getContainerType() == FL_CONTAINER_BLOCK)
			{
				bool bHead = (vBL.findItem(static_cast<fl_BlockLayout *>(b)) >= 0);
				queueBlockForBackgroundCheck(iReason, static_cast<fl_BlockLayout *>(b), bHead);
				b = static_cast<fl_BlockLayout *>(b)->getNextBlockInDocument();
			}
			else
			{
				b = b->getNext();
			}
		}
	}
}
