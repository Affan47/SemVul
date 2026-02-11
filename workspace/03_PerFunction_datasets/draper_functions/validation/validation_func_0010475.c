lpfc_disable_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp)
{
	lpfc_cancel_retry_delay_tmo(vport, ndlp);
	if (ndlp->nlp_state && !list_empty(&ndlp->nlp_listp))
		lpfc_nlp_counters(vport, ndlp->nlp_state, -1);
	lpfc_nlp_state_cleanup(vport, ndlp, ndlp->nlp_state,
				NLP_STE_UNUSED_NODE);
}
