acdInTypeSeqSave(const AjPStr intype)
{
    if(acdInTypeSeqName)
	return ajFalse;

    acdLog("acdInTypeSeqSave (%S)\n",
	   intype);

    if(!ajStrGetLen(intype))
    {
	ajStrAssignClear(&acdInTypeSeqName);
	acdLog("Input sequence type defaults to ''\n", acdInTypeSeqName);
	acdInTypeFeatSave(NULL);
    }
    else
    {
	ajStrAssignS(&acdInTypeSeqName, intype);
	ajStrFmtLower(&acdInTypeSeqName);

	if(ajSeqTypeIsAny(intype))
	    acdInTypeFeatSaveC("");
	else if(ajSeqTypeIsProt(intype))
	    acdInTypeFeatSaveC("protein");
	else if(ajSeqTypeIsNuc(intype))
	    acdInTypeFeatSaveC("nucleotide");
	else
	    acdInTypeFeatSaveC("");
    }

    acdLog("acdInTypeSeqSave (%S) input type set to '%S'\n",
	   intype, acdInTypeSeqName);

    return ajTrue;
}
