BWTSASSNewMRAEnc(const SASeqSrc *src)
{
  const BWTSASeqSrc *bwtSASeqSrc;
  gt_assert(src);
  bwtSASeqSrc = constSASS2BWTSASS(src);
  return gt_MRAEncCopy(EISGetAlphabet(BWTSeqGetEncIdxSeq(bwtSASeqSrc->bwtSeq)));
}
