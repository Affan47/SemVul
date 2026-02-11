vAddFooter(diagram_type *pDiag)
{
	const hdrftr_block_type *pFtrInfo;

	fail(pDiag == NULL);

	NO_DBG_MSG("vAddFooter");

	pFtrInfo = pGetHdrFtrInfo(iSectionIndex, FALSE,
					odd(iPageCount), bFirstInSection);
	bFirstInSection = FALSE;
	if (pFtrInfo == NULL ||
	    pFtrInfo->pText == NULL ||
	    pFtrInfo->lHeight <= 0) {
		fail(pFtrInfo != NULL && pFtrInfo->lHeight < 0);
		fail(pFtrInfo != NULL &&
			pFtrInfo->pText != NULL &&
			pFtrInfo->lHeight == 0);
		return;
	}

	bInFtrSpace = TRUE;

	DBG_DEC_C(pFtrInfo->lHeight != lFooterHeight, pFtrInfo->lHeight);
	DBG_DEC_C(pFtrInfo->lHeight != lFooterHeight, lFooterHeight);
	DBG_DEC_C(pDiag->lYtop < lFooterHeight + PS_BOTTOM_MARGIN,
			pDiag->lYtop);
	DBG_DEC_C(pDiag->lYtop < lFooterHeight + PS_BOTTOM_MARGIN,
			lFooterHeight + PS_BOTTOM_MARGIN);

	if (pDiag->lYtop > lFooterHeight + PS_BOTTOM_MARGIN) {

		pDiag->lYtop = lFooterHeight + PS_BOTTOM_MARGIN;
		vMoveTo(pDiag, 0);
	} else if (pDiag->lYtop < lFooterHeight + PS_BOTTOM_MARGIN / 2) {
		DBG_FIXME();


		pDiag->lYtop = lFooterHeight + PS_BOTTOM_MARGIN;
		vMoveTo(pDiag, 0);
	}

	DBG_FLT_C(pDiag->lYtop < lFooterHeight + PS_BOTTOM_MARGIN,
	dDrawUnits2Points(lFooterHeight + PS_BOTTOM_MARGIN - pDiag->lYtop));

	vAddHdrFtr(pDiag, pFtrInfo);
	bInFtrSpace = FALSE;
}
