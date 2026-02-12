void TDStretch::setTempo(double newTempo)
{
    int intskip;

    tempo = newTempo;


    calcSeqParameters();


    nominalSkip = tempo * (seekWindowLength - overlapLength);
    intskip = (int)(nominalSkip + 0.5);


    sampleReq = max(intskip + overlapLength, seekWindowLength) + seekLength;
}
