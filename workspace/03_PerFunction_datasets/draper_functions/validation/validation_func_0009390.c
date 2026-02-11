FSBlkDelElm(
	BTSK *		pStack)
{
	RCODE			rc;
	FLMBYTE*		pDelElm;
	FLMBYTE*		pCurElm;
	FLMBYTE*		pBlk = pStack->pBlk;

	FLMUINT		uiCurElmOfs;
	FLMUINT		uiDelElmPkc;
	FLMUINT		uiCurElmPkc;
	FLMUINT		uiCurElmKeyLen;
	FLMUINT		uiOldCurElm = pStack->uiCurElm;
	FLMUINT		uiElmOvhd = pStack->uiElmOvhd;
	FLMINT		iDelElmSize;
	FLMINT		iPkcLost;

	pDelElm = &pBlk[pStack->uiCurElm];

	if (RC_OK( rc = FSBlkNextElm( pStack)))
	{


		uiCurElmOfs = pStack->uiCurElm;
		iDelElmSize = (FLMINT) (uiCurElmOfs - uiOldCurElm);
		pCurElm = &pBlk[uiCurElmOfs];

		if (pStack->uiBlkType != BHT_NON_LEAF_DATA)
		{
			uiDelElmPkc = (FLMUINT) (BBE_GET_PKC( pDelElm));
			uiCurElmPkc = (FLMUINT) (BBE_GET_PKC( pCurElm));


			if (uiCurElmPkc > uiDelElmPkc)
			{
				iPkcLost = (FLMINT) (uiCurElmPkc - uiDelElmPkc);


				uiCurElmPkc -= iPkcLost;
				uiCurElmKeyLen = (FLMUINT) (BBE_GET_KL( pCurElm) + iPkcLost);

				BBE_SET_PKC( pDelElm, uiCurElmPkc);
				BBE_SET_KL( pDelElm, uiCurElmKeyLen);
				*pDelElm |= (FLMBYTE) (BBE_IS_FIRST_LAST( pCurElm));

				if (pStack->uiBlkType == BHT_LEAF)
				{
					BBE_SET_RL( pDelElm, BBE_GET_RL( pCurElm));
				}
				else
				{
					f_memcpy( pDelElm + BNE_CHILD_BLOCK, pCurElm + BNE_CHILD_BLOCK,
								uiElmOvhd - BNE_CHILD_BLOCK);
				}


				iDelElmSize -= iPkcLost;
				uiCurElmOfs += uiElmOvhd;


				f_memcpy( pDelElm + uiElmOvhd, &pStack->pKeyBuf[uiDelElmPkc],
							iPkcLost);


			}
		}


		shiftN( &pBlk[uiCurElmOfs], pStack->uiBlkEnd - uiCurElmOfs,
				 (FLMINT) (0 - iDelElmSize));

		pStack->uiBlkEnd -= iDelElmSize;
	}
	else if (rc == FERR_BT_END_OF_DATA)
	{
		rc = FERR_OK;
		if (pStack->uiCurElm == pStack->uiBlkEnd)
		{


			pStack->uiBlkEnd = uiOldCurElm;
		}
		else
		{


			pBlk[uiOldCurElm] = BBE_FIRST_FLAG | BBE_LAST_FLAG;
			pBlk[uiOldCurElm + BBE_KL] = pBlk[uiOldCurElm + BBE_RL] = 0;
			pStack->uiBlkEnd = uiOldCurElm + uiElmOvhd;
		}
	}
	else
	{
		goto Exit;
	}


	UW2FBA( (FLMUINT16) pStack->uiBlkEnd, &pBlk[BH_BLK_END]);
	pStack->uiCurElm = uiOldCurElm;

Exit:

	return (rc);
}
