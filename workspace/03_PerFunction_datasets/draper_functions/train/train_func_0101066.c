print(raw_ostream &OS) const {
  switch (Kind) {
  case Immediate:
    getImm()->print(OS);
    break;
  case Register:
    OS << "<register R";
    OS << getMBlazeRegisterNumbering(getReg()) << ">";
    break;
  case Token:
    OS << "'" << getToken() << "'";
    break;
  case Memory: {
    OS << "<memory R";
    OS << getMBlazeRegisterNumbering(getMemBase());
    OS << ", ";

    unsigned RegOff = getMemOffReg();
    if (RegOff)
      OS << "R" << getMBlazeRegisterNumbering(RegOff);
    else
      OS << getMemOff();
    OS << ">";
    }
    break;
  case Fsl:
    getFslImm()->print(OS);
    break;
  }
}
