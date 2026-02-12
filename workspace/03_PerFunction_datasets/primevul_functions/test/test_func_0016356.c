bool InstanceKlass::should_store_fingerprint(bool is_anonymous) {
#if INCLUDE_AOT

  if (CalculateClassFingerprint) {

    return true;
  }
  if (DumpSharedSpaces) {

    return true;
  }
  if (UseAOT && is_anonymous) {

    return true;
  }
#endif


  return false;
}
