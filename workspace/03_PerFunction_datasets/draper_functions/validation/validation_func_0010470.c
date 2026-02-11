getAnnotationRun(void)
{
        PT_DocPosition posFL = getDocPosition() - 1;
	fl_ContainerLayout * pPrevL = static_cast<fl_ContainerLayout *>(m_pLayout->findBlockAtPosition(posFL));


	if(pPrevL != NULL)
	{
		if(pPrevL->getContainerType() == FL_CONTAINER_BLOCK)
		{


			UT_ASSERT(pPrevL->getContainerType() == FL_CONTAINER_BLOCK);
			fl_BlockLayout * pBL = static_cast<fl_BlockLayout *>(pPrevL);
			fp_Run * pRun = pBL->getFirstRun();
			PT_DocPosition posBL = pBL->getPosition();
			while(pRun && ((posBL + pRun->getBlockOffset() + pRun->getLength()) <= posFL))
			{
				pRun = pRun->getNextRun();
			}
			if(pRun && (pRun->getType() == FPRUN_HYPERLINK))
			{
			    fp_HyperlinkRun * pHRun = static_cast<fp_HyperlinkRun *>(pRun);
			    if(pHRun->getHyperlinkType() == HYPERLINK_ANNOTATION)
			    {
				fp_AnnotationRun * pARun = static_cast<fp_AnnotationRun * >(pHRun);
				if(pARun->getPID() == getAnnotationPID())
				{
				    return pARun;
				}
			    }
			}
			else
			{
			    return NULL;
			}
		}
		else
	        {
		    return NULL;
		}
	}
	return NULL;
}
