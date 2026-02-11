getEmptyKey() {
    SmallVector<const SCEV *, 2> V;
    V.push_back(reinterpret_cast<const SCEV *>(-1));
    return V;
  }
