void TDStretch::processSamples()
{
    int ovlSkip;
    int offset = 0;
    int temp;


    while ((int)inputBuffer.numSamples() >= sampleReq)
    {
        if (isBeginning == false)
        {


            offset = seekBestOverlapPosition(inputBuffer.ptrBegin());


            overlap(outputBuffer.ptrEnd((uint)overlapLength), inputBuffer.ptrBegin(), (uint)offset);
            outputBuffer.putSamples((uint)overlapLength);
            offset += overlapLength;
        }
        else
        {


            isBeginning = false;
            int skip = (int)(tempo * overlapLength + 0.5);

            #ifdef SOUNDTOUCH_ALLOW_NONEXACT_SIMD_OPTIMIZATION
                #ifdef SOUNDTOUCH_ALLOW_SSE

                if (channels == 1)
                {
                    skip &= -4;
                }
                else if (channels == 2)
                {
                    skip &= -2;
                }
                #endif
            #endif
            skipFract -= skip;
            assert(nominalSkip >= -skipFract);
        }


        if ((int)inputBuffer.numSamples() < (offset + seekWindowLength - overlapLength))
        {
            continue;
        }


        temp = (seekWindowLength - 2 * overlapLength);
        outputBuffer.putSamples(inputBuffer.ptrBegin() + channels * offset, (uint)temp);


        assert((offset + temp + overlapLength) <= (int)inputBuffer.numSamples());
        memcpy(pMidBuffer, inputBuffer.ptrBegin() + channels * (offset + temp),
            channels * sizeof(SAMPLETYPE) * overlapLength);


        skipFract += nominalSkip;
        ovlSkip = (int)skipFract;
        skipFract -= ovlSkip;
        inputBuffer.receiveSamples((uint)ovlSkip);
    }
}
