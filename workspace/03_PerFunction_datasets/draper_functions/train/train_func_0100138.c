operator=(const CglStored& rhs)
{
  if (this != &rhs) {
    CglCutGenerator::operator=(rhs);
    requiredViolation_=rhs.requiredViolation_;
    cuts_=rhs.cuts_;
    delete probingInfo_;
    if (rhs.probingInfo_)
      probingInfo_ = new CglTreeProbingInfo(*rhs.probingInfo_);
    else
      probingInfo_ = NULL;
    delete [] bestSolution_;
    delete [] bounds_;
    bestSolution_ = NULL;
    bounds_ = NULL;
    numberColumns_ = rhs.numberColumns_;
    if (numberColumns_) {
      bestSolution_ = CoinCopyOfArray(rhs.bestSolution_,numberColumns_+1);
      bounds_ = CoinCopyOfArray(rhs.bounds_,2*numberColumns_);
    }
  }
  return *this;
}
