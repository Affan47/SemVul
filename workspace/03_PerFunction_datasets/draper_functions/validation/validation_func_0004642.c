mqc_renorme(opj_mqc_t *mqc) {
	do {
		mqc->a <<= 1;
		mqc->c <<= 1;
		mqc->ct--;
		if (mqc->ct == 0) {
			mqc_byteout(mqc);
		}
	} while ((mqc->a & 0x8000) == 0);
}
