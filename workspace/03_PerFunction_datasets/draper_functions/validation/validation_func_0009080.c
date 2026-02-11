bfa_itn_isr(struct bfa_s *bfa, struct bfi_msg_s *m)
{
	struct bfa_fcp_mod_s *fcp = BFA_FCP_MOD(bfa);
	union bfi_itn_i2h_msg_u msg;
	struct bfa_itn_s *itn;

	msg.msg = m;
	itn =  BFA_ITN_FROM_TAG(fcp, msg.create_rsp->bfa_handle);

	if (itn->isr)
		itn->isr(bfa, m);
	else
		WARN_ON(1);
}
