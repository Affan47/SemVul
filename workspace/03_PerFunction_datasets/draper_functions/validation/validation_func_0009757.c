CreatePileupData(void) {


    ClearOldData();


    CurrentPileupData.RefId = CurrentId;
    CurrentPileupData.Position = CurrentPosition;
    CurrentPileupData.PileupAlignments.clear();


    vector<BamAlignment>::const_iterator alIter = CurrentAlignments.begin();
    vector<BamAlignment>::const_iterator alEnd  = CurrentAlignments.end();
    for ( ; alIter != alEnd; ++alIter )
        ParseAlignmentCigar( (*alIter) );
}
