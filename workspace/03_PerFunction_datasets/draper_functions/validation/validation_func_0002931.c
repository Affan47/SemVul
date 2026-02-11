isBitShuffle(const MachineInstr *MI,
      unsigned DefR) const {
  unsigned Opc = MI->getOpcode();
  switch (Opc) {
    case TargetOpcode::COPY:
    case Hexagon::S2_lsr_i_r:
    case Hexagon::S2_asr_i_r:
    case Hexagon::S2_asl_i_r:
    case Hexagon::S2_lsr_i_p:
    case Hexagon::S2_asr_i_p:
    case Hexagon::S2_asl_i_p:
    case Hexagon::S2_insert:
    case Hexagon::A2_or:
    case Hexagon::A2_orp:
    case Hexagon::A2_and:
    case Hexagon::A2_andp:
    case Hexagon::A2_combinew:
    case Hexagon::A4_combineri:
    case Hexagon::A4_combineir:
    case Hexagon::A2_combineii:
    case Hexagon::A4_combineii:
    case Hexagon::A2_combine_ll:
    case Hexagon::A2_combine_lh:
    case Hexagon::A2_combine_hl:
    case Hexagon::A2_combine_hh:
      return true;
  }
  return false;
}
