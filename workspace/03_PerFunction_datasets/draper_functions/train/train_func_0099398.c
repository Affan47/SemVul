bfa_msgq_notify(void *cbarg, enum bfa_ioc_event event)
{
	struct bfa_msgq *msgq = (struct bfa_msgq *)cbarg;

	switch (event) {
	case BFA_IOC_E_ENABLED:
		bfa_wc_init(&msgq->init_wc, bfa_msgq_init, msgq);
		bfa_wc_up(&msgq->init_wc);
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_START);
		bfa_wc_up(&msgq->init_wc);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_START);
		bfa_wc_wait(&msgq->init_wc);
		break;

	case BFA_IOC_E_DISABLED:
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_STOP);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_STOP);
		break;

	case BFA_IOC_E_FAILED:
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_FAIL);
		bfa_fsm_send_event(&msgq->rspq, RSPQ_E_FAIL);
		break;

	default:
		break;
	}
}
