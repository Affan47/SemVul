splitBlockBeforeInstr(MachineInstr *MI) {
  MachineBasicBlock *OrigBB = MI->getParent();


  MachineBasicBlock *NewBB =
    MF->CreateMachineBasicBlock(OrigBB->getBasicBlock());
  MachineFunction::iterator MBBI = ++OrigBB->getIterator();
  MF->insert(MBBI, NewBB);


  NewBB->splice(NewBB->end(), OrigBB, MI, OrigBB->end());


  unsigned Opc = isThumb ? (isThumb2 ? ARM::t2B : ARM::tB) : ARM::B;
  if (!isThumb)
    BuildMI(OrigBB, DebugLoc(), TII->get(Opc)).addMBB(NewBB);
  else
    BuildMI(OrigBB, DebugLoc(), TII->get(Opc)).addMBB(NewBB)
            .addImm(ARMCC::AL).addReg(0);
  ++NumSplit;


  NewBB->transferSuccessors(OrigBB);


  OrigBB->addSuccessor(NewBB);


  MF->RenumberBlocks(NewBB);


  BBInfo.insert(BBInfo.begin() + NewBB->getNumber(), BasicBlockInfo());


  water_iterator IP =
    std::lower_bound(WaterList.begin(), WaterList.end(), OrigBB,
                     CompareMBBNumbers);
  MachineBasicBlock* WaterBB = *IP;
  if (WaterBB == OrigBB)
    WaterList.insert(std::next(IP), NewBB);
  else
    WaterList.insert(IP, OrigBB);
  NewWaterList.insert(OrigBB);


  computeBlockSize(OrigBB);


  computeBlockSize(NewBB);


  adjustBBOffsetsAfter(OrigBB);

  return NewBB;
}
