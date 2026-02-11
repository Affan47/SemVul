ksr(pkmsg, pkmsg2)

struct kmsg		*pkmsg;
struct kmsg		*pkmsg2;

{
	int4		r;
	int4		sv_length;

	sv_length = pkmsg->k_length;


	do {
		pkmsg->k_length = sv_length;

		if (ksrfront(pkmsg, pkmsg2) < 0) {
			return(LAMERROR);
		}

		r = ksrback(pkmsg2);

	} while ((r > 0) && ((r & _kio.ki_sigretry) == r));

	if (r > 0) {
		errno = EINTR;
		return(LAMERROR);
	} else if (r < 0) {
		return(LAMERROR);
	}

	return(0);
}
