getYoffsetFromTable(fp_Container * pT,
													fp_Container* pCell,
													fp_ContainerObject * pCon)
{
	fp_TableContainer * pFirstTable = static_cast<fp_TableContainer *>(pT)->getFirstBrokenTable();
	fp_TableContainer * pTable = pFirstTable;

	UT_sint32 offset = 0;
	bool bFound = false;
	while(pTable != NULL && !bFound)
	{
		bFound = pTable->isInBrokenTable(static_cast<fp_CellContainer *>(pCell),static_cast<fp_Container *>(pCon));
		if(bFound)
		{
			offset = -pTable->getYBreak();
		}
		pTable = static_cast<fp_TableContainer *>(pTable->getNext());
	}
	return offset;
}
