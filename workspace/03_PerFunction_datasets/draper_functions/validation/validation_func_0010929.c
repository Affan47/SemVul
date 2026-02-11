stun_agent_forget_transaction (StunAgent *agent, StunTransactionId id)
{
  int i;

  for (i = 0; i < STUN_AGENT_MAX_SAVED_IDS; i++) {
    if (agent->sent_ids[i].valid == TRUE &&
        memcmp (id, agent->sent_ids[i].id,
            sizeof(StunTransactionId)) == 0) {
      agent->sent_ids[i].valid = FALSE;
      return TRUE;
    }
  }

  return FALSE;
}
