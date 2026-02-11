giextract_encodedseq2fasta(FILE *fpout,
                                      const GtEncseq *encseq,
                                      unsigned long seqnum,
                                      const Fastakeyquery *fastakeyquery,
                                      unsigned long linewidth,
                                      GT_UNUSED GtError *err)
{
  const char *desc;
  unsigned long desclen;
  bool haserr = false;

  desc = gt_encseq_description(encseq, &desclen, seqnum);
  gt_xfputc('>',fpout);
  if (fastakeyquery != NULL && !COMPLETE(fastakeyquery))
  {
    printf("%s %lu %lu ",fastakeyquery->fastakey,
                         fastakeyquery->frompos,
                         fastakeyquery->topos);
  }
  gt_xfwrite(desc,sizeof *desc,(size_t) desclen,fpout);
  if (!haserr)
  {
    unsigned long frompos, topos, seqstartpos, seqlength ;

    gt_xfputc('\n',fpout);
    seqstartpos = gt_encseq_seqstartpos(encseq, seqnum);
    seqlength = gt_encseq_seqlength(encseq, seqnum);
    if (fastakeyquery != NULL && !COMPLETE(fastakeyquery))
    {
      frompos = fastakeyquery->frompos-1;
      topos = fastakeyquery->topos - fastakeyquery->frompos + 1;
    } else
    {
      frompos = 0;
      topos = seqlength;
    }
    gt_encseq2symbolstring(fpout,
                           encseq,
                           GT_READMODE_FORWARD,
                           seqstartpos + frompos,
                           topos,
                           linewidth);
  }
  return haserr ? -1 : 0;
}
