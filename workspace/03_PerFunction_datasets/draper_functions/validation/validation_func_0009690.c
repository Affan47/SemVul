collapse(void)
{
	_localCollapse();
	fp_AnnotationContainer *pAC = static_cast<fp_AnnotationContainer *>(getFirstContainer());
	if (pAC)
	{


		if(pAC->getPage())
		{
			pAC->getPage()->removeAnnotationContainer(pAC);
			pAC->setPage(NULL);
		}


		fp_AnnotationContainer * pPrev = static_cast<fp_AnnotationContainer *>(pAC->getPrev());
		if(pPrev)
		{
			pPrev->setNext(pAC->getNext());
		}
		if(pAC->getNext())
		{
			pAC->getNext()->setPrev(pPrev);
		}
		delete pAC;
	}
	setFirstContainer(NULL);
	setLastContainer(NULL);
	m_bIsOnPage = false;
}
