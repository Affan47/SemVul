OnTestEnd(const TestInfo& test_info) {
  if (test_info.result()->Passed()) {
    ColoredPrintf(COLOR_GREEN, "[       OK ] ");
  } else {
    ColoredPrintf(COLOR_RED, "[  FAILED  ] ");
  }
  PrintTestName(test_case_name_.c_str(), test_info.name());
  if (GTEST_FLAG(print_time)) {
    printf(" (%s ms)\n", internal::StreamableToString(
           test_info.result()->elapsed_time()).c_str());
  } else {
    printf("\n");
  }
  fflush(stdout);
}
