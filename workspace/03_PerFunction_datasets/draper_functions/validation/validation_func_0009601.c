ajSeqcvtGetCodeAsymS (const AjPSeqCvt cvt, const AjPStr str)
{
    ajint i=0;

    for(i=0;i<cvt->nclabels;i++)
	if(ajStrMatchS(str, cvt->clabels[i]))
	    return i+1;


    ajWarn("Sequence character string not found in ajSeqcvtGetCodeAsymS");
    return 0;
}
