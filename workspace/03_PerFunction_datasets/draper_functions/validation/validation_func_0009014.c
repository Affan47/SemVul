setGraphics(GR_Graphics * pG)
{
  m_pG = pG;
  if(isDefault())
  {
    UT_sint32 i =0;
    for(i=0; i< m_vecSnapshots.getItemCount(); i++)
      {
	GR_EmbedView * pEView = m_vecSnapshots.getNthItem(i);
	DELETEP(pEView->m_pPreview);
      }
  }
}
