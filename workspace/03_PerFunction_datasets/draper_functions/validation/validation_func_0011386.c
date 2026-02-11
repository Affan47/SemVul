getSubTarget(MCInstrInfo const &MCII,
                                     MCInst const &MCI) {
  const uint64_t F = HexagonMCInstrInfo::getDesc(MCII, MCI).TSFlags;

  HexagonII::SubTarget Target = static_cast<HexagonII::SubTarget>(
      (F >> HexagonII::validSubTargetPos) & HexagonII::validSubTargetMask);

  switch (Target) {
  default:
    return Hexagon::ArchV4;
  case HexagonII::HasV5SubT:
    return Hexagon::ArchV5;
  }
}
