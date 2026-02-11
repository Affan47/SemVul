ajBtreePriNew(void)
{
    AjPBtPri pri = NULL;


    if(statSaveBtreePriNext)
    {
        pri = statSaveBtreePri[--statSaveBtreePriNext];
        MAJSTRASSIGNCLEAR(&pri->id);
        MAJSTRASSIGNCLEAR(&pri->keyword);
        pri->treeblock = 0UL;
    }
    else
    {
        AJNEW0(pri);
        pri->keyword   = ajStrNew();
        pri->id        = ajStrNew();
        pri->treeblock = 0UL;
    }

    return pri;
}
