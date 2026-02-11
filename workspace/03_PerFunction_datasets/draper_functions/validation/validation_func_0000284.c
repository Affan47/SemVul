eloList(const PartialDate date) const
{
    const int year = date.year();
    if(year < 1971)
    {
        return 0;
    }
    if(year < 2001)
    {
        return ((year - 1971) * 2) + 1 + (date.month() / 7);
    }
    return 60 + ((year - 2001) * 4) + 1 + (date.month() / 4);
}
