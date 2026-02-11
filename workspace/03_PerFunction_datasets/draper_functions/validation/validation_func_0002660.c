calculateDustScore(const std::string& seq)
{
    std::map<std::string, int> scoreMap;


    if(seq.size() < 3)
        return 0.0f;


    for(size_t i = 0; i < seq.size() - 3; ++i)
    {
        std::string triMer = seq.substr(i, 3);
        scoreMap[triMer]++;
    }


    double sum = 0;
    std::map<std::string, int>::iterator iter = scoreMap.begin();
    for(; iter != scoreMap.end(); ++iter)
    {
        int tc = iter->second;
        double score = (double)(tc * (tc - 1)) / 2.0f;
        sum += score;
    }
    return sum / (seq.size() - 2);
}
