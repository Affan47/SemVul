_KrefQuickSort(
	FLMUINT *		puiQsortFlags,
	KREF_ENTRY **	pEntryTbl,
	FLMUINT			uiLowerBounds,
	FLMUINT			uiUpperBounds)
{
	FLMUINT			uiLBPos;
	FLMUINT			uiUBPos;
	FLMUINT			uiMIDPos;
	FLMUINT			uiLeftItems;
	FLMUINT			uiRightItems;
	KREF_ENTRY *	pCurEntry;
	KREF_ENTRY *	pTempKref;
	FLMINT			iCompare;

Iterate_Larger_Half:

	uiUBPos = uiUpperBounds;
	uiLBPos = uiLowerBounds;
	uiMIDPos = (uiUpperBounds + uiLowerBounds + 1) / 2;
	pCurEntry = pEntryTbl[uiMIDPos];
	for (;;)
	{
		while( (uiLBPos == uiMIDPos) || ((iCompare = _KrefCompare( puiQsortFlags,
			pEntryTbl[uiLBPos], pCurEntry)) < 0))
		{
			if (uiLBPos >= uiUpperBounds)
			{
				break;
			}

			uiLBPos++;
		}

		while ((uiUBPos == uiMIDPos) || (((iCompare = _KrefCompare(
			puiQsortFlags, pCurEntry, pEntryTbl[uiUBPos])) < 0)))
		{
			if (!uiUBPos)
			{
				break;
			}

			uiUBPos--;
		}

		if (uiLBPos < uiUBPos)
		{


			KY_SWAP( pEntryTbl, uiLBPos, uiUBPos);
			uiLBPos++;
			uiUBPos--;
		}
		else
		{
			break;
		}
	}


	if (uiLBPos < uiMIDPos)
	{


		KY_SWAP( pEntryTbl, uiMIDPos, uiLBPos);
		uiMIDPos = uiLBPos;
	}
	else if (uiMIDPos < uiUBPos)
	{


		KY_SWAP( pEntryTbl, uiMIDPos, uiUBPos);
		uiMIDPos = uiUBPos;
	}


	uiLeftItems = (uiLowerBounds + 1 < uiMIDPos)
									? uiMIDPos - uiLowerBounds
									: 0;

	uiRightItems = (uiMIDPos + 1 < uiUpperBounds)
									? uiUpperBounds - uiMIDPos
									: 0;

	if (uiLeftItems < uiRightItems)
	{


		if (uiLeftItems)
		{
			(void) _KrefQuickSort( puiQsortFlags, pEntryTbl, uiLowerBounds,
										 uiMIDPos - 1);
		}

		uiLowerBounds = uiMIDPos + 1;
		goto Iterate_Larger_Half;
	}
	else if (uiLeftItems)
	{


		if (uiRightItems)
		{
			(void) _KrefQuickSort( puiQsortFlags, pEntryTbl, uiMIDPos + 1,
										 uiUpperBounds);
		}

		uiUpperBounds = uiMIDPos - 1;
		goto Iterate_Larger_Half;
	}

	return (FERR_OK);
}
