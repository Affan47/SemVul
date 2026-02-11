markDirtyOverlappingRuns(UT_Rect & recScreen)
{
	UT_Rect * pRec = NULL;
	pRec = getScreenRect();
	if(pRec && recScreen.intersectsRect(pRec))
	{
		DELETEP(pRec);
		UT_sint32 count = countCons();
		UT_sint32 i = 0;
		for(i = 0; i < count;i++)
		{
			fp_Container * pCon = static_cast<fp_Container * >(getNthCon(i));
			pCon->markDirtyOverlappingRuns(recScreen);
		}
		return;
	}
	DELETEP(pRec);
}
