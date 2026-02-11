LayoutOnce(MCAsmLayout &Layout) {
  ++stats::RelaxationSteps;

  bool WasRelaxed = false;
  for (iterator it = begin(), ie = end(); it != ie; ++it) {
    MCSectionData &SD = *it;
    while(LayoutSectionOnce(Layout, SD))
      WasRelaxed = true;
  }

  return WasRelaxed;
}
