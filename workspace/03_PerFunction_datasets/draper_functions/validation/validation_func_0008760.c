getSuccWeight(MachineBasicBlock *succ) {
  if (Weights.empty())
    return 0;

  succ_iterator I = std::find(Successors.begin(), Successors.end(), succ);
  return *getWeightIterator(I);
}
