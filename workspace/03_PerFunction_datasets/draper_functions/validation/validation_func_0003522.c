addressRangeContainsAddress(
    const DWARFUnit *U, const uint64_t Address) const {
  for (const auto& R : getAddressRanges(U)) {
    if (R.first <= Address && Address < R.second)
      return true;
  }
  return false;
}
