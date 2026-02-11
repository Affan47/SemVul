ScaNonDbgReleaseForThread(
	SCACHE *		pSCache)
{
	if (pSCache->uiUseCount)
	{
		pSCache->uiUseCount--;
		gv_FlmSysData.SCacheMgr.uiTotalUses--;
		if (!pSCache->uiUseCount)
		{
			gv_FlmSysData.SCacheMgr.uiBlocksUsed--;
		}
	}
}
