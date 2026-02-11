checkVariableRange(UChar32 ch) const {
    return !(ch >= curData->variablesBase && ch < variableLimit);
}
