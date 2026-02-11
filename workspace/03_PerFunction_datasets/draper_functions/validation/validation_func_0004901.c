ajSeqGapStandard(AjPSeq seq, char gapchar)
{
    char newgap = '-';
    static char testchars[] = "-~.? ";
    char *testgap;

    testgap = testchars;

    if(gapchar)
	newgap = gapchar;


    while(*testgap)
    {
	if(newgap != *testgap)
	{
	    ajStrExchangeKK(&seq->Seq, *testgap, newgap);


	}

	testgap++;
    }

    return;
}
