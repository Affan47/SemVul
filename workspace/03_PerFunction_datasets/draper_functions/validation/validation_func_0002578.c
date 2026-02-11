LexExclaim() {
  if (!isalpha(*CurPtr))
    return ReturnError(CurPtr - 1, "Invalid \"!operator\"");

  const char *Start = CurPtr++;
  while (isalpha(*CurPtr))
    ++CurPtr;


  tgtok::TokKind Kind =
    StringSwitch<tgtok::TokKind>(StringRef(Start, CurPtr - Start))
    .Case("eq", tgtok::XEq)
    .Case("if", tgtok::XIf)
    .Case("head", tgtok::XHead)
    .Case("tail", tgtok::XTail)
    .Case("con", tgtok::XConcat)
    .Case("shl", tgtok::XSHL)
    .Case("sra", tgtok::XSRA)
    .Case("srl", tgtok::XSRL)
    .Case("cast", tgtok::XCast)
    .Case("empty", tgtok::XEmpty)
    .Case("subst", tgtok::XSubst)
    .Case("foreach", tgtok::XForEach)
    .Case("strconcat", tgtok::XStrConcat)
    .Default(tgtok::Error);

  return Kind != tgtok::Error ? Kind : ReturnError(Start-1, "Unknown operator");
}
