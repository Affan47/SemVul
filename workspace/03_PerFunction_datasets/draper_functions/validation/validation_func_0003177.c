ParseDirectiveSymver(StringRef, SMLoc) {
  StringRef Name;
  if (getParser().ParseIdentifier(Name))
    return TokError("expected identifier in directive");

  if (getLexer().isNot(AsmToken::Comma))
    return TokError("expected a comma");

  Lex();

  StringRef AliasName;
  if (getParser().ParseIdentifier(AliasName))
    return TokError("expected identifier in directive");

  if (AliasName.find('@') == StringRef::npos)
    return TokError("expected a '@' in the name");

  MCSymbol *Alias = getContext().GetOrCreateSymbol(AliasName);
  MCSymbol *Sym = getContext().GetOrCreateSymbol(Name);
  const MCExpr *Value = MCSymbolRefExpr::Create(Sym, getContext());

  getStreamer().EmitAssignment(Alias, Value);
  return false;
}
