bfa_itnim_create(struct bfa_s *bfa, struct bfa_rport_s *rport, void *ditn)
{
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	struct bfa_itnim_s *itnim;

	bfa_itn_create(bfa, rport, bfa_itnim_isr);

	itnim = BFA_ITNIM_FROM_TAG(fcpim, rport->rport_tag);
	WARN_ON(itnim->rport != rport);

	itnim->ditn = ditn;

	bfa_stats(itnim, creates);
	bfa_sm_send_event(itnim, BFA_ITNIM_SM_CREATE);

	return itnim;
}
