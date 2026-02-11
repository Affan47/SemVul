isTriviallyReplacablePHI(const PHINode &PN, const Instruction &I) {
  for (const Value *IncValue : PN.incoming_values())
    if (IncValue != &I)
      return false;

  return true;
}
