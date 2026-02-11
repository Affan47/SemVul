redrawUpdate(void)
{
	if(!isOnScreen())
		return false;

	UT_sint32 count = m_vecRuns.getItemCount();
	if(count)
	{
		draw(m_vecRuns.getNthItem(0)->getGraphics());
	}

	m_bNeedsRedraw = false;
	return true;
}
