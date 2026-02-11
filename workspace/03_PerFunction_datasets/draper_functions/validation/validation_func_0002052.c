getAllUsedStyles(UT_GenericVector <PD_Style*>* pVecStyles)
{
	UT_sint32 i = 0;
	pf_Frag * currentFrag = m_pPieceTable->getFragments().getFirst();
	PD_Style * pStyle = NULL;
	while (currentFrag!=m_pPieceTable->getFragments().getLast())
	{
		UT_return_if_fail (currentFrag);


		PT_AttrPropIndex indexAP = 0;
		if(currentFrag->getType()  == pf_Frag::PFT_Strux)
			indexAP = static_cast<pf_Frag_Strux *>(currentFrag)->getIndexAP();
		else if(currentFrag->getType()  == pf_Frag::PFT_Text)
			indexAP = static_cast<pf_Frag_Text *>(currentFrag)->getIndexAP();
		else if(currentFrag->getType()  == pf_Frag::PFT_Object)
			indexAP = static_cast<pf_Frag_Object *>(currentFrag)->getIndexAP();
		else if(currentFrag->getType()  == pf_Frag::PFT_FmtMark)
			indexAP = static_cast<pf_Frag_FmtMark *>(currentFrag)->getIndexAP();
		const PP_AttrProp * pAP = NULL;
		m_pPieceTable->getAttrProp(indexAP,&pAP);
		UT_return_if_fail (pAP);
		const gchar * pszStyleName = NULL;
		(pAP)->getAttribute(PT_STYLE_ATTRIBUTE_NAME, pszStyleName);


		if(pszStyleName != NULL)
		{
			m_pPieceTable->getStyle(pszStyleName,&pStyle);
			UT_return_if_fail (pStyle);
			if(pStyle)
			{
				if(pVecStyles->findItem(pStyle) < 0)
					pVecStyles->addItem(pStyle);
				PD_Style * pBasedOn = pStyle->getBasedOn();
				i = 0;
				while(pBasedOn != NULL && i <  pp_BASEDON_DEPTH_LIMIT)
				{
					if(pVecStyles->findItem(pBasedOn) < 0)
						pVecStyles->addItem(pBasedOn);
					i++;
					pBasedOn = pBasedOn->getBasedOn();
				}
				PD_Style * pFollowedBy = pStyle->getFollowedBy();
				if(pFollowedBy && (pVecStyles->findItem(pFollowedBy) < 0))
					pVecStyles->addItem(pFollowedBy);
			}
		}


		currentFrag = currentFrag->getNext();
	}


}
