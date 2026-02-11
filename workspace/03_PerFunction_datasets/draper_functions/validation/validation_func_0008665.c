gt_callenumquerymatches_withindex(
                            GtQuerysubstringmatchfunc findquerymatches,
                            const Suffixarray *suffixarray,
                            const GtStrArray *queryfiles,
                            bool forwardstrand,
                            bool reversestrand,
                            unsigned int userdefinedleastlength,
                            GtProcessquerybeforematching
                               processquerybeforematching,
                            GtProcessquerymatch processquerymatch,
                            void *processquerymatchinfo,
                            GtError *err)
{
  GtSeqIterator *seqit;
  bool haserr = false;

  seqit = gt_seq_iterator_sequence_buffer_new(queryfiles, err);
  if (seqit == NULL)
  {
    haserr = true;
  } else
  {
    GtQuerymatch *querymatchspaceptr = gt_querymatch_new();
    const GtUchar *query;
    unsigned long querylen;
    int retval;
    uint64_t queryunitnum;
    GtUchar *queryreverse = NULL;
    unsigned long queryreverse_length = 0;
    char *desc = NULL;
    int mode;

    gt_seq_iterator_set_symbolmap(seqit,
                    gt_alphabet_symbolmap(gt_encseq_alphabet(
                                                        suffixarray->encseq)));
    for (queryunitnum = 0; ; queryunitnum++)
    {
      retval = gt_seq_iterator_next(seqit, &query, &querylen, &desc, err);
      if (retval < 0)
      {
        haserr = true;
        break;
      }
      if (retval == 0)
      {
        break;
      }
      if (querylen >= (unsigned long) userdefinedleastlength)
      {
        GtQueryrep queryrep;

        queryrep.encseq = NULL;
        queryrep.readmode = GT_READMODE_FORWARD;
        queryrep.startpos = 0;
        queryrep.length = querylen;
        for (mode = 0; mode <= 1; mode++)
        {
          if (mode == 0 && forwardstrand)
          {
            queryrep.sequence = query;
            queryrep.reversecopy = false;
            if (processquerybeforematching != NULL)
            {
              processquerybeforematching(processquerymatchinfo,desc,query,
                                         querylen,true);
            }
          } else
          {
            if (mode == 1 && reversestrand)
            {
              if (querylen > queryreverse_length)
              {
                queryreverse = gt_realloc(queryreverse,
                                          sizeof (*queryreverse) * querylen);
                queryreverse_length = querylen;
              }
              gt_copy_reversecomplement(queryreverse,query,querylen);
              queryrep.sequence = queryreverse;
              queryrep.reversecopy = true;
              if (processquerybeforematching != NULL)
              {
                processquerybeforematching(processquerymatchinfo,desc,
                                           queryreverse,querylen,false);
              }
            } else
            {
              queryrep.sequence = NULL;
              queryrep.reversecopy = false;
            }
          }
          if (queryrep.sequence != NULL)
          {
            int ret = findquerymatches(false,
                                       suffixarray,
                                       queryunitnum,
                                       &queryrep,
                                       (unsigned long) userdefinedleastlength,
                                       processquerymatch,
                                       processquerymatchinfo,
                                       querymatchspaceptr,
                                       err);
            if (ret != 0)
            {
              haserr = true;
              break;
            }
          }
        }
      }
    }
    gt_seq_iterator_delete(seqit);
    gt_free(queryreverse);
    gt_querymatch_delete(querymatchspaceptr);
  }
  return haserr ? -1 : 0;
}
