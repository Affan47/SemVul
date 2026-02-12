bool Strobelight::active() {
  if (rds::isFullyInitialized() && isXenonActive()) {

    return false;
  }


  return FOLLY_SDT_IS_ENABLED(hhvm, hhvm_stack);
}
