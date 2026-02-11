read() {
  while (!at_eof()) {
    auto NumHeadSamples = readNumber<uint64_t>();
    if (std::error_code EC = NumHeadSamples.getError())
      return EC;

    auto FName(readStringFromTable());
    if (std::error_code EC = FName.getError())
      return EC;

    Profiles[*FName] = FunctionSamples();
    FunctionSamples &FProfile = Profiles[*FName];

    FProfile.addHeadSamples(*NumHeadSamples);

    if (std::error_code EC = readProfile(FProfile))
      return EC;
  }

  return sampleprof_error::success;
}
