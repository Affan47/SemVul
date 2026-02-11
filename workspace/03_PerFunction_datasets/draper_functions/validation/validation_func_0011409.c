GetDotNewOp(const MachineInstr* MI) const {
  int NVOpcode = Hexagon::getNewValueOpcode(MI->getOpcode());
  if (NVOpcode >= 0)
    return NVOpcode;

  switch (MI->getOpcode()) {
  default: llvm_unreachable("Unknown .new type");
  case Hexagon::S4_storerb_ur:
    return Hexagon::S4_storerbnew_ur;

  case Hexagon::S4_storerh_ur:
    return Hexagon::S4_storerhnew_ur;

  case Hexagon::S4_storeri_ur:
    return Hexagon::S4_storerinew_ur;

  case Hexagon::S2_storerb_pci:
    return Hexagon::S2_storerb_pci;

  case Hexagon::S2_storeri_pci:
    return Hexagon::S2_storeri_pci;

  case Hexagon::S2_storerh_pci:
    return Hexagon::S2_storerh_pci;

  case Hexagon::S2_storerd_pci:
    return Hexagon::S2_storerd_pci;

  case Hexagon::S2_storerf_pci:
    return Hexagon::S2_storerf_pci;
  }
  return 0;
}
