GetBinCost() const
{
    double binCost = 0.0;
    for (PBins::const_iterator bit = _bins.begin(); bit != _bins.end(); bit++)
    {
        binCost += Abs((*bit)->GetSize() - (*bit)->GetCapa());
    }
    return binCost;
}
