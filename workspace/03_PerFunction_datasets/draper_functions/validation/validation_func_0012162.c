main(int argc, const char *argv[]) {
  sys::PrintStackTraceOnErrorSignal();
  PrettyStackTraceProgram X(argc, argv);
  llvm_shutdown_obj Y;


  cl::AddExtraVersionPrinter(TargetRegistry::printRegisteredTargetsForVersion);

  cl::ParseCommandLineOptions(argc, argv, "LLVM Object Reader\n");


  if (opts::InputFilenames.size() == 0)
    opts::InputFilenames.push_back("-");

  std::for_each(opts::InputFilenames.begin(), opts::InputFilenames.end(),
                dumpInput);

  return 0;
}
