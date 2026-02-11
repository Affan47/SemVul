dump() const {
  if (Addr == 0) {
    dbgs() << "PHITransAddr: null\n";
    return;
  }
  dbgs() << "PHITransAddr: " << *Addr << "\n";
  for (unsigned i = 0, e = InstInputs.size(); i != e; ++i)
    dbgs() << "  Input #" << i << " is " << *InstInputs[i] << "\n";
}
