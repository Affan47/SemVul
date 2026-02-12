static void huft_free(huft_t *p)
{
	huft_t *q;


	if (BAD_HUFT(p)) {
		p = (huft_t*)((uintptr_t)(p) ^ (uintptr_t)(ERR_RET));
	}


	while (p) {
		q = (--p)->v.t;
		free(p);
		p = q;
	}
}
