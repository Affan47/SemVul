_cmsFreeInterpParams(cmsInterpParams* p)
{
    if (p != NULL) _cmsFree(p ->ContextID, p);
}
