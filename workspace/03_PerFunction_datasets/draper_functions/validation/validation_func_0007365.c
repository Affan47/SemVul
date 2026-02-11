ajRangeIsWhole(const AjPRange thys, const AjPSeq s)
{


    if(thys->n == 0)
    {
        ajDebug("ajRangeDefault n:%d begin:%u end:%u\n",
                thys->n,
                ajSeqGetBegin(s), ajSeqGetEnd(s));

        return ajTrue;
    }

    ajDebug("ajRangeDefault n:%d start:%d end:%d begin:%u end:%u\n",
            thys->n, thys->start[0], thys->end[0],
            ajSeqGetBegin(s), ajSeqGetEnd(s));


    return ajFalse;
}
