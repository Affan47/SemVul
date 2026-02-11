bAddDummyImagePS(diagram_type *pDiag, const imagedata_type *pImg)
{
	FILE	*pOutFile;

	fail(pDiag == NULL);
	fail(pDiag->pOutFile == NULL);
	fail(pImg == NULL);

	if (pImg->iVerSizeScaled <= 0 || pImg->iHorSizeScaled <= 0) {
		return FALSE;
	}

	iImageCount++;

	DBG_DEC_C(pDiag->lXleft != 0, pDiag->lXleft);

	pDiag->lYtop -= lPoints2DrawUnits(pImg->iVerSizeScaled);
	vMoveTo(pDiag, lPoints2DrawUnits(pImg->iVerSizeScaled));

	pOutFile = pDiag->pOutFile;

	fprintf(pOutFile, "gsave %% Image %03d\n", iImageCount);
	fprintf(pOutFile, "\tnewpath\n");
	fprintf(pOutFile, "\t%.2f %.2f moveto\n",
			dDrawUnits2Points(pDiag->lXleft + PS_LEFT_MARGIN),
			dDrawUnits2Points(pDiag->lYtop));
	fprintf(pOutFile, "\t1.0 setlinewidth\n");
	fprintf(pOutFile, "\t0.3 setgray\n");
	fprintf(pOutFile, "\t0 %d rlineto\n", pImg->iVerSizeScaled);
	fprintf(pOutFile, "\t%d 0 rlineto\n", pImg->iHorSizeScaled);
	fprintf(pOutFile, "\t0 %d rlineto\n", -pImg->iVerSizeScaled);
	fprintf(pOutFile, "\tclosepath\n");
	fprintf(pOutFile, "\tstroke\n");
	fprintf(pOutFile, "grestore\n");

	pDiag->lXleft = 0;

	return TRUE;
}
