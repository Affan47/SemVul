LexTokenATT() {
  AsmToken lexedToken = lexDefinite();

  switch (lexedToken.getKind()) {
  default:
    return lexedToken;
  case AsmToken::Error:
    SetError(Lexer->getErrLoc(), Lexer->getErr());
    return lexedToken;

  case AsmToken::Percent: {
    const AsmToken &nextToken = lexTentative();
    if (nextToken.getKind() != AsmToken::Identifier)
      return lexedToken;


    if (unsigned regID = MatchRegisterName(nextToken.getString())) {
      lexDefinite();


      StringRef regStr(lexedToken.getString().data(),
                       lexedToken.getString().size() +
                       nextToken.getString().size());

      return AsmToken(AsmToken::Register, regStr,
                      static_cast<int64_t>(regID));
    }


    if (nextToken.getString().size() == 3 &&
        nextToken.getString().startswith("db")) {
      int RegNo = -1;
      switch (nextToken.getString()[2]) {
      case '0': RegNo = X86::DR0; break;
      case '1': RegNo = X86::DR1; break;
      case '2': RegNo = X86::DR2; break;
      case '3': RegNo = X86::DR3; break;
      case '4': RegNo = X86::DR4; break;
      case '5': RegNo = X86::DR5; break;
      case '6': RegNo = X86::DR6; break;
      case '7': RegNo = X86::DR7; break;
      }

      if (RegNo != -1) {
        lexDefinite();


        StringRef regStr(lexedToken.getString().data(),
                         lexedToken.getString().size() +
                         nextToken.getString().size());
        return AsmToken(AsmToken::Register, regStr,
                        static_cast<int64_t>(RegNo));
      }
    }


    return lexedToken;
  }
  }
}
