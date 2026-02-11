seqTypeCharNucPure(void)
{
    AjPStr regstr = NULL;
    AjPStr tmpstr = NULL;

    if(!seqtypeRegNucPure)
    {
	regstr = ajStrNewRes(256);
	tmpstr = ajStrNewS(seqTypeStrNucPure());

	ajStrAppendC(&regstr, "([^");
	ajStrKeepSetAlpha(&tmpstr);
	ajStrFmtLower(&tmpstr);
	ajStrAppendS(&regstr, tmpstr);
	ajStrAppendS(&regstr, seqTypeStrNucPure());
	ajStrAppendC(&regstr, "+])");

	seqtypeRegNucPure = ajRegComp(regstr);

	ajStrDel(&regstr);
	ajStrDel(&tmpstr);
    }

    return seqtypeRegNucPure;
}
