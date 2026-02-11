isProfitableToIfCvt(MachineBasicBlock &TMBB,
                    unsigned TCycles, unsigned TExtra,
                    MachineBasicBlock &FMBB,
                    unsigned FCycles, unsigned FExtra,
                    BranchProbability Probability) const {
  if (!TCycles || !FCycles)
    return false;


  const unsigned ScalingUpFactor = 1024;
  unsigned TUnpredCost = Probability.scale(TCycles * ScalingUpFactor);
  unsigned FUnpredCost =
      Probability.getCompl().scale(FCycles * ScalingUpFactor);
  unsigned UnpredCost = TUnpredCost + FUnpredCost;
  UnpredCost += 1 * ScalingUpFactor;
  UnpredCost += Subtarget.getMispredictionPenalty() * ScalingUpFactor / 10;

  return (TCycles + FCycles + TExtra + FExtra) * ScalingUpFactor <= UnpredCost;
}
