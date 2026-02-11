GetColIx(const int ix) const
{
    int ret = -1;
    if (ix == COL_RANKING)
    {
        ret = 0;
    }
    else if (ix == COL_DATE)
    {
        ret = 1;
    }
    else if (ix == COL_TIME)
    {
        ret = 2;
    }
    else if (ix == COL_DELETE)
    {
        ret = 3;
    }
    return ret;
}
