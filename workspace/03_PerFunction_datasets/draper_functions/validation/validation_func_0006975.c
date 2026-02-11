GamutSampler(register const cmsUInt16Number In[], register cmsUInt16Number Out[], register void* Cargo)
{
    GAMUTCHAIN*  t = (GAMUTCHAIN* ) Cargo;
    cmsCIELab LabIn1, LabOut1;
    cmsCIELab LabIn2, LabOut2;
    cmsUInt16Number Proof[cmsMAXCHANNELS], Proof2[cmsMAXCHANNELS];
    cmsFloat64Number dE1, dE2, ErrorRatio;


    ErrorRatio = 1.0;


    cmsDoTransform(t -> hInput, In, &LabIn1, 1);


    cmsDoTransform(t -> hForward, &LabIn1, Proof, 1);


    cmsDoTransform(t -> hReverse, Proof, &LabOut1, 1);

    memmove(&LabIn2, &LabOut1, sizeof(cmsCIELab));


    cmsDoTransform(t -> hForward, &LabOut1, Proof2, 1);
    cmsDoTransform(t -> hReverse, Proof2, &LabOut2, 1);


    dE1 = cmsDeltaE(&LabIn1, &LabOut1);


    dE2 = cmsDeltaE(&LabIn2, &LabOut2);


    if (dE1 < t->Thereshold && dE2 < t->Thereshold)
        Out[0] = 0;
    else {


        if (dE1 < t->Thereshold && dE2 > t->Thereshold)
            Out[0] = 0;
        else

            if (dE1 > t->Thereshold && dE2 < t->Thereshold)
                Out[0] = (cmsUInt16Number) _cmsQuickFloor((dE1 - t->Thereshold) + .5);
            else  {


                if (dE2 == 0.0)
                    ErrorRatio = dE1;
                else
                    ErrorRatio = dE1 / dE2;

                if (ErrorRatio > t->Thereshold)
                    Out[0] = (cmsUInt16Number)  _cmsQuickFloor((ErrorRatio - t->Thereshold) + .5);
                else
                    Out[0] = 0;
            }
    }


    return TRUE;
}
