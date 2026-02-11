nullPointerError(const Token *tok, const std::string &varname, bool inconclusive)
{
    reportError(tok, Severity::error, "nullPointer", "Possible null pointer dereference: " + varname, inconclusive);
}
