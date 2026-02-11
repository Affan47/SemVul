writeProgramToFileAux(tool_output_file &Out, const Module *M) {
  WriteBitcodeToFile(M, Out.os(), PreserveBitcodeUseListOrder);
  Out.os().close();
  if (!Out.os().has_error()) {
    Out.keep();
    return false;
  }
  return true;
}
