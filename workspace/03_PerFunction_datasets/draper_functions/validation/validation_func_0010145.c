lpfc_rcv_prli_npr_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		       void *arg, uint32_t evt)
{
	struct Scsi_Host  *shost = lpfc_shost_from_vport(vport);
	struct lpfc_iocbq *cmdiocb = (struct lpfc_iocbq *) arg;
	struct ls_rjt     stat;

	memset(&stat, 0, sizeof (struct ls_rjt));
	stat.un.b.lsRjtRsnCode = LSRJT_UNABLE_TPC;
	stat.un.b.lsRjtRsnCodeExp = LSEXP_NOTHING_MORE;
	lpfc_els_rsp_reject(vport, stat.un.lsRjtError, cmdiocb, ndlp, NULL);

	if (!(ndlp->nlp_flag & NLP_DELAY_TMO)) {
		if (ndlp->nlp_flag & NLP_NPR_ADISC) {
			spin_lock_irq(shost->host_lock);
			ndlp->nlp_flag &= ~NLP_NPR_ADISC;
			ndlp->nlp_prev_state = NLP_STE_NPR_NODE;
			spin_unlock_irq(shost->host_lock);
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_ADISC_ISSUE);
			lpfc_issue_els_adisc(vport, ndlp, 0);
		} else {
			ndlp->nlp_prev_state = NLP_STE_NPR_NODE;
			lpfc_nlp_set_state(vport, ndlp, NLP_STE_PLOGI_ISSUE);
			lpfc_issue_els_plogi(vport, ndlp->nlp_DID, 0);
		}
	}
	return ndlp->nlp_state;
}
