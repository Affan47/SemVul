hasVRegCycleUse(const SUnit *SU) {

  if (SU->isVRegCycle)
    return false;

  for (SUnit::const_pred_iterator I = SU->Preds.begin(),E = SU->Preds.end();
       I != E; ++I) {
    if (I->isCtrl()) continue;
    if (I->getSUnit()->isVRegCycle &&
        I->getSUnit()->getNode()->getOpcode() == ISD::CopyFromReg) {
      DEBUG(dbgs() << "  VReg cycle use: SU (" << SU->NodeNum << ")\n");
      return true;
    }
  }
  return false;
}
