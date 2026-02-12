void RegisterInternalHandlers() {

  if (!TrustedPrimitives::RegisterEntryHandler(kSelectorAsyloDonateThread,
                                               EntryHandler{DonateThread})
           .ok()) {
    TrustedPrimitives::BestEffortAbort(
        "Could not register entry handler: DonateThread.");
  }


  if (!TrustedPrimitives::RegisterEntryHandler(kSelectorAsyloFini,
                                               EntryHandler{FinalizeEnclave})
           .ok()) {
    TrustedPrimitives::BestEffortAbort(
        "Could not register entry handler: FinalizeEnclave");
  }
}
