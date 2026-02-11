tryAllocateResourcesForConstExt(MachineInstr* MI) {
  const HexagonInstrInfo *QII = (const HexagonInstrInfo *) TII;
  MachineInstr *PseudoMI = MF.CreateMachineInstr(QII->get(Hexagon::A4_ext),
                                                 MI->getDebugLoc());

  if (ResourceTracker->canReserveResources(PseudoMI)) {
    ResourceTracker->reserveResources(PseudoMI);
    MI->getParent()->getParent()->DeleteMachineInstr(PseudoMI);
    return true;
  } else {
    MI->getParent()->getParent()->DeleteMachineInstr(PseudoMI);
    return false;
  }
}
