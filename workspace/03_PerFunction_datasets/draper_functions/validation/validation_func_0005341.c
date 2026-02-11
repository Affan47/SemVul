ParseDagArgList(Record *CurRec) {
  std::vector<std::pair<llvm::Init*, std::string> > Result;

  while (1) {
    Init *Val = ParseValue(CurRec);
    if (Val == 0) return std::vector<std::pair<llvm::Init*, std::string> >();


    std::string VarName;
    if (Lex.getCode() == tgtok::colon) {
      if (Lex.Lex() != tgtok::VarName) {
        TokError("expected variable name in dag literal");
        return std::vector<std::pair<llvm::Init*, std::string> >();
      }
      VarName = Lex.getCurStrVal();
      Lex.Lex();
    }

    Result.push_back(std::make_pair(Val, VarName));

    if (Lex.getCode() != tgtok::comma) break;
    Lex.Lex();
  }

  return Result;
}
