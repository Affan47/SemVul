vl_aib_min_beta
(VlAIB * aib, vl_uint * besti, vl_uint * bestj, double * minbeta)
{
    vl_uint i;
    *minbeta = aib->beta[0];
    *besti   = 0;
    *bestj   = aib->bidx[0];

    for(i=0; i<aib->nentries; i++)
    {
        if(aib->beta[i] < *minbeta)
        {
            *minbeta = aib->beta[i];
            *besti = i;
            *bestj = aib->bidx[i];
        }
    }
}
