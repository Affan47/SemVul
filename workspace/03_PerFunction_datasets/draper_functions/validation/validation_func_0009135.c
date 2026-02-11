aliasPHI(const PHINode *PN, uint64_t PNSize,
                             const MDNode *PNTBAAInfo,
                             const Value *V2, uint64_t V2Size,
                             const MDNode *V2TBAAInfo) {


  if (const PHINode *PN2 = dyn_cast<PHINode>(V2))
    if (PN2->getParent() == PN->getParent()) {
      AliasResult Alias =
        aliasCheck(PN->getIncomingValue(0), PNSize, PNTBAAInfo,
                   PN2->getIncomingValueForBlock(PN->getIncomingBlock(0)),
                   V2Size, V2TBAAInfo);
      if (Alias == MayAlias)
        return MayAlias;
      for (unsigned i = 1, e = PN->getNumIncomingValues(); i != e; ++i) {
        AliasResult ThisAlias =
          aliasCheck(PN->getIncomingValue(i), PNSize, PNTBAAInfo,
                     PN2->getIncomingValueForBlock(PN->getIncomingBlock(i)),
                     V2Size, V2TBAAInfo);
        Alias = MergeAliasResults(ThisAlias, Alias);
        if (Alias == MayAlias)
          break;
      }
      return Alias;
    }

  SmallPtrSet<Value*, 4> UniqueSrc;
  SmallVector<Value*, 4> V1Srcs;
  for (unsigned i = 0, e = PN->getNumIncomingValues(); i != e; ++i) {
    Value *PV1 = PN->getIncomingValue(i);
    if (isa<PHINode>(PV1))


      return MayAlias;
    if (UniqueSrc.insert(PV1))
      V1Srcs.push_back(PV1);
  }

  AliasResult Alias = aliasCheck(V2, V2Size, V2TBAAInfo,
                                 V1Srcs[0], PNSize, PNTBAAInfo);


  if (Alias == MayAlias)
    return MayAlias;


  for (unsigned i = 1, e = V1Srcs.size(); i != e; ++i) {
    Value *V = V1Srcs[i];

    AliasResult ThisAlias = aliasCheck(V2, V2Size, V2TBAAInfo,
                                       V, PNSize, PNTBAAInfo);
    Alias = MergeAliasResults(ThisAlias, Alias);
    if (Alias == MayAlias)
      break;
  }

  return Alias;
}
