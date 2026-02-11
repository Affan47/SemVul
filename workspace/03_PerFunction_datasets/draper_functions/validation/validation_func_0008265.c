finishBlockStack() {

  if (MBB->succ_empty())
    return;

  DEBUG(dbgs() << "Setting up live-outs for BB#" << MBB->getNumber()
               << " derived from " << MBB->getName() << ".\n");

  unsigned BundleIdx = BlockBundle.lookup(MBB).second;
  LiveBundle &Bundle = LiveBundles[BundleIdx];


  MachineBasicBlock::iterator Term = MBB->getFirstTerminator();
  adjustLiveRegs(Bundle.Mask, Term);

  if (!Bundle.Mask) {
    DEBUG(dbgs() << "No live-outs.\n");
    return;
  }


  DEBUG(dbgs() << "LB#" << BundleIdx << ": ");
  if (Bundle.isFixed()) {
    DEBUG(dbgs() << "Shuffling stack to match.\n");
    shuffleStackTop(Bundle.FixStack, Bundle.FixCount, Term);
  } else {

    DEBUG(dbgs() << "Fixing stack order now.\n");
    Bundle.FixCount = StackTop;
    for (unsigned i = 0; i < StackTop; ++i)
      Bundle.FixStack[i] = getStackEntry(i);
  }
}
