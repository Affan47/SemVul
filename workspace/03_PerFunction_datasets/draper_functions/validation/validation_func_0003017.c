bfa_ioc_fw_mismatch(struct bfa_ioc_s *ioc)
{
	return bfa_fsm_cmp_state(ioc, bfa_ioc_sm_reset) ||
		bfa_fsm_cmp_state(&ioc->iocpf, bfa_iocpf_sm_fwcheck) ||
		bfa_fsm_cmp_state(&ioc->iocpf, bfa_iocpf_sm_mismatch);
}
