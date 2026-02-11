unlinkFromRunList()
{


	if(getType() == FPRUN_HYPERLINK)
	{
		fp_HyperlinkRun * pH = static_cast<fp_HyperlinkRun*>(this);
		if(pH->isStartOfHyperlink())
		{
			fp_Run * pRun = getNextRun();

			while(pRun && pRun->getHyperlink() == pH)
			{
				pRun->setHyperlink(NULL);
				pRun = pRun->getNextRun();
			}
		}
	}

	if (m_pPrev)
	{
		m_pPrev->setNextRun(m_pNext);
	}
	if (m_pNext)
	{
		m_pNext->setPrevRun(m_pPrev);
		setNextRun(0);
	}
	setPrevRun(0);
}
