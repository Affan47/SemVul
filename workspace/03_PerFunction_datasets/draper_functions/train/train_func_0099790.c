ServerSocket_setReceiveBufferSize(CTX ctx, ksfp_t *sfp _RIX)
{
	knh_serversocket_t *ss = (knh_serversocket_t *)((sfp[0].p)->rawptr);
	int ret = Int_to(int, sfp[1]);
	unsigned int len = sizeof(ret);
	if(setsockopt(ss->sd, SOL_SOCKET, SO_RCVBUF, &ret, len) == -1) {
		KNH_NTRACE2(ctx, "setsockopt", K_PERROR, KNH_LDATA(LOG_i("sd", ss->sd), LOG_i("port", ss->port)));
		ret = 0;
	} else {
		KNH_NTRACE2(ctx, "setsockopt", K_OK, KNH_LDATA(LOG_i("sd", ss->sd), LOG_i("port", ss->port)));
	}
	RETURNi_(ret);
}
