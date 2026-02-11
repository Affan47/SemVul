countSequenceOccurrences(const std::string& w, const BWT* pBWT)
{
    BWTInterval fwd_interval = findInterval(pBWT, w);
    BWTInterval rc_interval = findInterval(pBWT, reverseComplement(w));

    size_t count = 0;
    if(fwd_interval.isValid())
        count += fwd_interval.size();
    if(rc_interval.isValid())
        count += rc_interval.size();
    return count;
}
