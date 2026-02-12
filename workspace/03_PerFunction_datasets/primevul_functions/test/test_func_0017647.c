is_anon_tgs_request_p(const KDC_REQ_BODY *b,
		      const EncTicketPart *tgt)
{
    KDCOptions f = b->kdc_options;


    return tgt->flags.anonymous ||
	(f.request_anonymous && !f.cname_in_addl_tkt && !b->additional_tickets);
}
