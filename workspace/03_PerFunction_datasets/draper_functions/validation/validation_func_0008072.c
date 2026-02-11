MarkLive(const RetOrArg &RA) {
  if (LiveFunctions.count(RA.F))
    return;

  if (!LiveValues.insert(RA).second)
    return;

  DEBUG(dbgs() << "DAE - Marking " << RA.getDescription() << " live\n");
  PropagateLiveness(RA);
}
