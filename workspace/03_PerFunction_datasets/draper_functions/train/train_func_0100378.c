issamearch(ap1, ap2)
CONST archive_t *ap1, *ap2;
{
	if (!(ap1 -> p_comm)) {
		if (ap2 -> p_comm) return(0);
	}
	else if (!(ap2 -> p_comm)) return(0);
	else if (strcommcmp(ap1 -> p_comm, ap2 -> p_comm)) return(0);
	if (strcommcmp(ap1 -> u_comm, ap2 -> u_comm)) return(0);

	return(1);
}
