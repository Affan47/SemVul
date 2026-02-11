_cio_kreqfront(struct kreq *pkq)
{


	if (mwrite(sd_kernel, (char *) pkq, sizeof(struct kreq)) <
			(int)sizeof(struct kreq)) {

		if (errno == EPIPE) {

			if (pkq->kq_req != KQATTACH) {
				exit(ENOKERNEL);
			} else {
				errno = ENOKERNEL;
			}
		}

		return(LAMERROR);
	}

	return(sd_kernel);
}
