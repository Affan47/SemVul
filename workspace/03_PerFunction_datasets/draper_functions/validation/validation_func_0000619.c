ajFeatGetParent(const AjPFeature thys)
{
    AjIList iter;
    AjPTagval tv = NULL;

    if(!thys)
        return NULL;

    if(!ajListGetLength(thys->GffTags))
        return NULL;

    iter = ajListIterNewread(thys->GffTags);

    while(!ajListIterDone(iter))
    {
        tv = ajListIterGet(iter);

        if(ajStrMatchC(MAJTAGVALGETTAG(tv), "Parent"))
        {
            ajListIterDel(&iter);
            return MAJTAGVALGETVALUE(tv);
        }
    }

    return NULL;
}
