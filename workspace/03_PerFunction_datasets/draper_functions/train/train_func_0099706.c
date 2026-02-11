resetAlign()
{


    register int sl;
    int i, j;
    int _gapPos1 = userParameters->getGapPos1();
    int _gapPos2 = userParameters->getGapPos2();
    bool _resetAlignNew = userParameters->getResetAlignmentsNew();
    bool _resetAlignAll = userParameters->getResetAlignmentsAll();


    for(i = 1; i <= numSeqs;++i)
    {
        sl = 0;
        for(j = 1; j <= getSeqLength(i); ++j)
        {
            if(seqArray[i][j] == _gapPos1 && ( _resetAlignNew || _resetAlignAll))
            {
                continue;
            }
            if(seqArray[i][j] == _gapPos2 && (_resetAlignAll))
            {
                continue;
            }
            ++sl;
            seqArray[i][sl] = seqArray[i][j];
        }


        int numExtraElements = seqArray[i].size() - 1 - sl;
        for(int k = 0; k < numExtraElements; k++)
        {
            seqArray[i].pop_back();
        }
    }
}
