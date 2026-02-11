run(Function &F) {
  DominatorTree DT;
  DT.recalculate(F);
  return DT;
}
