_deleteSpan(void)
{
       pf_Frag * pfOld = NULL;
       pf_Frag * pf = m_fragObject.getNext();
       while (pf&&pf->getType()==pf_Frag::PFT_Text&&
	      pf->getField()==this)
       {
	     pfOld = pf;
	     pf = pfOld->getNext();
	     m_pPieceTable->deleteFieldFrag(pfOld);
       }
       return true;
}
