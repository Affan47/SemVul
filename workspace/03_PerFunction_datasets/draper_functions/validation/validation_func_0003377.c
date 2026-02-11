ev_store(Window win, int type) {
	if (type == EV_RESET)  {
		n_CN = 0; n_RN = 0; n_DN = 0; n_ON = 0; n_MN = 0; n_UN = 0;
		n_VN = 0; n_VN_p = 0; n_VN_u = 0; n_ST = 0; n_PN = 0; n_DC = 0;
		n_ON_sz = 0; n_ON_po = 0; n_ON_st = 0;
		_ev_list_cnt = 0;
		return 1;
	}
	if (_ev_list_cnt >= EVLISTMAX) {
		return 0;
	}
	_ev_list[_ev_list_cnt] = win;
	_ev_case[_ev_list_cnt++] = type;
	return 1;
}
