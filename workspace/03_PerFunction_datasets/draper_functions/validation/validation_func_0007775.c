read() {
  line_iterator LineIt(*Buffer, true, '#');

  InlineCallStack InlineStack;

  for (; !LineIt.is_at_eof(); ++LineIt) {
    if ((*LineIt)[(*LineIt).find_first_not_of(' ')] == '#')
      continue;


    if ((*LineIt)[0] != ' ') {
      uint64_t NumSamples, NumHeadSamples;
      StringRef FName;
      if (!ParseHead(*LineIt, FName, NumSamples, NumHeadSamples)) {
        reportError(LineIt.line_number(),
                    "Expected 'mangled_name:NUM:NUM', found " + *LineIt);
        return sampleprof_error::malformed;
      }
      Profiles[FName] = FunctionSamples();
      FunctionSamples &FProfile = Profiles[FName];
      FProfile.addTotalSamples(NumSamples);
      FProfile.addHeadSamples(NumHeadSamples);
      InlineStack.clear();
      InlineStack.push_back(&FProfile);
    } else {
      uint64_t NumSamples;
      StringRef FName;
      DenseMap<StringRef, uint64_t> TargetCountMap;
      bool IsCallsite;
      uint32_t Depth, LineOffset, Discriminator;
      if (!ParseLine(*LineIt, IsCallsite, Depth, NumSamples, LineOffset,
                     Discriminator, FName, TargetCountMap)) {
        reportError(LineIt.line_number(),
                    "Expected 'NUM[.NUM]: NUM[ mangled_name:NUM]*', found " +
                        *LineIt);
        return sampleprof_error::malformed;
      }
      if (IsCallsite) {
        while (InlineStack.size() > Depth) {
          InlineStack.pop_back();
        }
        FunctionSamples &FSamples = InlineStack.back()->functionSamplesAt(
            CallsiteLocation(LineOffset, Discriminator, FName));
        FSamples.addTotalSamples(NumSamples);
        InlineStack.push_back(&FSamples);
      } else {
        while (InlineStack.size() > Depth) {
          InlineStack.pop_back();
        }
        FunctionSamples &FProfile = *InlineStack.back();
        for (const auto &name_count : TargetCountMap) {
          FProfile.addCalledTargetSamples(LineOffset, Discriminator,
                                          name_count.first, name_count.second);
        }
        FProfile.addBodySamples(LineOffset, Discriminator, NumSamples);
      }
    }
  }

  return sampleprof_error::success;
}
