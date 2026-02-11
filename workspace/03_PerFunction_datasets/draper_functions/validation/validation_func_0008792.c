ProcessFailure(StringRef ProgPath, const char** Args,
                                  unsigned Timeout = 0,
                                  unsigned MemoryLimit = 0) {
  std::ostringstream OS;
  OS << "\nError running tool:\n ";
  for (const char **Arg = Args; *Arg; ++Arg)
    OS << " " << *Arg;
  OS << "\n";


  SmallString<128> ErrorFilename;
  std::error_code EC = sys::fs::createTemporaryFile(
      "bugpoint.program_error_messages", "", ErrorFilename);
  if (EC) {
    errs() << "Error making unique filename: " << EC.message() << "\n";
    exit(1);
  }

  RunProgramWithTimeout(ProgPath, Args, "", ErrorFilename.str(),
                        ErrorFilename.str(), Timeout, MemoryLimit);


  std::ifstream ErrorFile(ErrorFilename.c_str());
  if (ErrorFile) {
    std::copy(std::istreambuf_iterator<char>(ErrorFile),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(OS));
    ErrorFile.close();
  }

  sys::fs::remove(ErrorFilename.c_str());
  return OS.str();
}
