amdlibIsP2VMUsable(amdlibSCIENCE_DATA *scienceData,
                                 amdlibP2VM_MATRIX  *p2vm,
                                 amdlibDOUBLE              *percentage)
{
    amdlibBOOLEAN isUsable;
    int l;
    int nbCovSpecChannels;
    int nbTel;
    isUsable = amdlibTRUE;

    amdlibLogTrace("amdlibIsP2VMUsable()");


    if (p2vm->thisPtr != p2vm)
    {
        amdlibInitP2VM(p2vm);
    }


    nbTel = scienceData->nbCols-1;
    if (nbTel == 1)
    {
        isUsable = amdlibFALSE;
        *percentage = 0.0;
    }
    else if ((nbTel == 3) && (p2vm->type == amdlibP2VM_2T))
    {
        isUsable = amdlibFALSE;
        *percentage = 0.0;
    }

    else if (p2vm->nx != scienceData->col[amdlibINTERF_CHANNEL].nbPixels)
    {
        isUsable = amdlibFALSE;
        *percentage = 0.0;
    }
    else
    {

        nbCovSpecChannels = 0;

        for (l = 0; l < scienceData->nbChannels; l++)
        {

            if ((scienceData->channelNo[l] >= p2vm->firstChannel) &&
                (scienceData->channelNo[l] <= (p2vm->firstChannel +
                                               p2vm->nbChannels)))
            {

                nbCovSpecChannels++;
            }
        }


        if (nbCovSpecChannels != 0)
        {
            isUsable = amdlibTRUE;
            *percentage = 100.0 *
            (amdlibDOUBLE)nbCovSpecChannels/(amdlibDOUBLE)scienceData->nbChannels;
        }
        else
        {
            isUsable = amdlibFALSE;
            *percentage = 0.0;
        }
        isUsable = amdlibTRUE;
    }
    return (isUsable);
}
