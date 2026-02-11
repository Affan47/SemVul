ensIntronsupportingevidenceTransfer(
    EnsPIntronsupportingevidence ise,
    EnsPSlice slice)
{
    EnsPFeature newfeature = NULL;

    EnsPIntronsupportingevidence newise = NULL;

    if (!ise)
        return NULL;

    if (!slice)
        return NULL;

    newfeature = ensFeatureTransfer(ise->Feature, slice);

    if (!newfeature)
        return NULL;

    newise = ensIntronsupportingevidenceNewCpy(ise);

    ensIntronsupportingevidenceSetFeature(newise, newfeature);

    return newise;
}
