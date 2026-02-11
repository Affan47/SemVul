GetScore() const
{
    if (mCombinationsCnt == 0 || mRowsCnt == 0 || mTime == 0)
    {
        return 0;
    }

    double dd = mCombinationsCnt * 10000;
    double dv = mRowsCnt * mTime / 100;
    return int(dd / dv);
}
