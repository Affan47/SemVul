int EstimateTAC(register const cmsUInt16Number In[], register cmsUInt16Number Out[], register void * Cargo)
{
    cmsTACestimator* bp = (cmsTACestimator*) Cargo;
    cmsFloat32Number RoundTrip[cmsMAXCHANNELS];
    cmsUInt32Number i;
    cmsFloat32Number Sum;


    cmsDoTransform(bp->hRoundTrip, In, RoundTrip, 1);


    for (Sum=0, i=0; i < bp ->nOutputChans; i++)
            Sum += RoundTrip[i];


    if (Sum > bp ->MaxTAC) {

            bp ->MaxTAC = Sum;

            for (i=0; i < bp ->nOutputChans; i++) {
                bp ->MaxInput[i] = In[i];
            }
    }

    return TRUE;

    cmsUNUSED_PARAMETER(Out);
}
