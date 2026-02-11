updateLayout(bool )
{
	bool bredraw = false;
	xxx_UT_DEBUGMSG(("Doing Update layout in shadow %x \n",this));
	fl_ContainerLayout*	pBL = getFirstLayout();
	m_vecFormatLayout.clear();
	while (pBL)
	{
		if (pBL->needsReformat())
		{
			bredraw = true;
			pBL->format();
		}

		pBL = pBL->getNext();
	}
	if(bredraw)
	{

		static_cast<fp_ShadowContainer *>(getFirstContainer())->layout();
 	}
}
