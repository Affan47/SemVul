mismatchAllocDealloc(const std::list<const Token *> &callstack, const std::string &varname) const
{
    reportErr(callstack, Severity::error, "mismatchAllocDealloc", "Mismatching allocation and deallocation: " + varname);
}
