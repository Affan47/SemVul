ike_phase_1_recv_KE_NONCE(struct message *msg)
{

	if (ipsec_save_g_x(msg)) {

		return -1;
	}

	if (exchange_save_nonce(msg)) {

		return -1;
	}

	if (exchange_save_certreq(msg)) {

		return -1;
	}
#if defined (USE_NAT_TRAVERSAL)

	if (msg->exchange->type == ISAKMP_EXCH_ID_PROT &&
	    msg->exchange->flags & EXCHANGE_FLAG_NAT_T_CAP_PEER)
		(void)nat_t_exchange_check_nat_d(msg);
#endif
	return 0;
}
