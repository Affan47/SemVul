getWeightsFromDistMat(vector<int>* seqWeights, DistMatrix* distMat,
                                     Alignment *alignPtr, int seq1, int nSeqs,
                                     string* phylipName, bool* success)
{
    if(userParameters->getClusterAlgorithm() == UPGMA)
    {
        getWeightsFromDistMatUPGMA(seqWeights, distMat, alignPtr, seq1, nSeqs, phylipName,
                                   success);
    }
    else
    {
        getWeightsFromDistMatNJ(seqWeights, distMat, alignPtr, seq1, nSeqs, phylipName,
                                success);
    }
}
