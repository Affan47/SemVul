dirvote_free_all(void)
{
  dirvote_clear_votes(1);

  smartlist_free(pending_vote_list);
  pending_vote_list = NULL;
  smartlist_free(previous_vote_list);
  previous_vote_list = NULL;

  dirvote_clear_pending_consensuses();
  tor_free(pending_consensus_signatures);
  if (pending_consensus_signature_list) {

    smartlist_free(pending_consensus_signature_list);
    pending_consensus_signature_list = NULL;
  }
}
