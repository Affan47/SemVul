amdlibAllocateOiTarget(amdlibOI_TARGET *target,
                                        const int       nbElements)
{
    amdlibLogTrace("amdlibAllocateOiTarget()");


    if (target->thisPtr == target)
    {
        amdlibFreeOiTarget(target);
    }


    target->thisPtr = memset(target, '\0', sizeof(*target));

    target->nbTargets = nbElements;


    if (nbElements > 0)
    {
        target->element = calloc(nbElements, sizeof(*(target->element)));
        if (target->element == NULL)
        {
            amdlibFreeOiTarget(target);
            return amdlibFAILURE;
        }
    }

    return amdlibSUCCESS;
}
