RestrictingDepExistInPacket(
    MachineInstr *MI, unsigned DepReg,
    const std::map<MachineInstr *, SUnit *> &MIToSUnit) {

  const HexagonInstrInfo *QII = (const HexagonInstrInfo *) TII;
  SUnit *PacketSUDep = MIToSUnit.find(MI)->second;

  for (std::vector<MachineInstr*>::iterator VIN = CurrentPacketMIs.begin(),
       VEN = CurrentPacketMIs.end(); (VIN != VEN); ++VIN) {


    if(!QII->isPredicated(*VIN)) continue;


    SUnit *PacketSU = MIToSUnit.find(*VIN)->second;


    if (PacketSU->isSucc(PacketSUDep)) {
      for (unsigned i = 0; i < PacketSU->Succs.size(); ++i) {
        if ((PacketSU->Succs[i].getSUnit() == PacketSUDep) &&
            (PacketSU->Succs[i].getKind() == SDep::Anti) &&
            (PacketSU->Succs[i].getReg() == DepReg)) {
          return true;
        }
      }
    }
  }

  return false;
}
