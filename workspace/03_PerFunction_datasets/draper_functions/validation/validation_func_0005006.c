initEmptySuperBlock(struct superBlock *sBlock,
                    const struct blockCompositionSeq *seqIdx)
{
  if (!seqIdxUsesMMap(seqIdx))
  {
    size_t offset;
    sBlock->cwData = (BitString)
      ((char *)sBlock + (offset = offsetAlign(sizeof (*sBlock),
                                              sizeof (BitElem))));
    sBlock->varData = (BitString)
      ((char *)sBlock + (offset = offsetAlign(offset
                                              + superBlockCWMaxReadSize(seqIdx),
                                              sizeof (BitElem))));
  }
}
