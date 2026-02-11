p7_hmm_ScoreDataCreate(P7_OPROFILE *om, int do_opt_ext )
{
  P7_SCOREDATA *data = NULL;
  int    status;

  ESL_ALLOC(data, sizeof(P7_SCOREDATA));

  data->msv_scores      = NULL;
  data->opt_ext_fwd     = NULL;
  data->opt_ext_rev     = NULL;
  data->prefix_lengths  = NULL;
  data->suffix_lengths  = NULL;
  data->fwd_scores      = NULL;
  data->fwd_transitions = NULL;

  scoredata_GetMSVScoreArrays(om, data, do_opt_ext);

  return data;

ERROR:
 p7_hmm_ScoreDataDestroy(data);
 return NULL;
}
