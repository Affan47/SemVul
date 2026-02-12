respip_inform_super(struct module_qstate* qstate, int id,
	struct module_qstate* super)
{
	struct respip_qstate* rq = (struct respip_qstate*)super->minfo[id];
	struct reply_info* new_rep = NULL;

	rq->state = RESPIP_SUBQUERY_FINISHED;


	log_assert(super->return_msg && super->return_msg->rep);


	if(!qstate->return_msg || !qstate->return_msg->rep ||
		qstate->return_rcode != LDNS_RCODE_NOERROR)
		goto fail;

	if(!respip_merge_cname(super->return_msg->rep, &qstate->qinfo,
		qstate->return_msg->rep, super->client_info,
		super->env->need_to_validate, &new_rep, super->region))
		goto fail;
	super->return_msg->rep = new_rep;
	return;

  fail:
	super->return_rcode = LDNS_RCODE_SERVFAIL;
	super->return_msg = NULL;
	return;
}
