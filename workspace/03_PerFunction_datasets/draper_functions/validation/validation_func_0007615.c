AnalyzeBranch(MachineBasicBlock &MBB,
                                   MachineBasicBlock *&TBB,
                                   MachineBasicBlock *&FBB,
                                   SmallVectorImpl<MachineOperand> &Cond,
                                   bool AllowModify) const
{

  MachineBasicBlock::iterator I = MBB.end();
  MachineBasicBlock::iterator UnCondBrIter = MBB.end();
  while (I != MBB.begin()) {
    --I;

    if (I->isDebugValue())
      continue;


    if (!isUnpredicatedTerminator(I))
      break;


    if (!I->getDesc().isBranch())
      return true;


    if (I->getOpcode() == SP::BA) {
      UnCondBrIter = I;

      if (!AllowModify) {
        TBB = I->getOperand(0).getMBB();
        continue;
      }

      while (llvm::next(I) != MBB.end())
        llvm::next(I)->eraseFromParent();

      Cond.clear();
      FBB = 0;

      if (MBB.isLayoutSuccessor(I->getOperand(0).getMBB())) {
        TBB = 0;
        I->eraseFromParent();
        I = MBB.end();
        UnCondBrIter = MBB.end();
        continue;
      }

      TBB = I->getOperand(0).getMBB();
      continue;
    }

    unsigned Opcode = I->getOpcode();
    if (Opcode != SP::BCOND && Opcode != SP::FBCOND)
      return true;

    SPCC::CondCodes BranchCode = (SPCC::CondCodes)I->getOperand(1).getImm();

    if (Cond.empty()) {
      MachineBasicBlock *TargetBB = I->getOperand(0).getMBB();
      if (AllowModify && UnCondBrIter != MBB.end() &&
          MBB.isLayoutSuccessor(TargetBB)) {


        BranchCode = GetOppositeBranchCondition(BranchCode);
        MachineBasicBlock::iterator OldInst = I;
        BuildMI(MBB, UnCondBrIter, MBB.findDebugLoc(I), get(Opcode))
          .addMBB(UnCondBrIter->getOperand(0).getMBB()).addImm(BranchCode);
        BuildMI(MBB, UnCondBrIter, MBB.findDebugLoc(I), get(SP::BA))
          .addMBB(TargetBB);
        MBB.addSuccessor(TargetBB);
        OldInst->eraseFromParent();
        UnCondBrIter->eraseFromParent();

        UnCondBrIter = MBB.end();
        I = MBB.end();
        continue;
      }
      FBB = TBB;
      TBB = I->getOperand(0).getMBB();
      Cond.push_back(MachineOperand::CreateImm(BranchCode));
      continue;
    }


    return true;
  }
  return false;
}
