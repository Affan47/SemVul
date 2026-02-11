loadfreq(
	int	ident,
	double	freq
	)
{
	struct freqmsg cmd = {V_SFREQ, 0, 0, 0, 0, FI, FI};
	u_char rsp[BMAX];
	int temp;

	if (flags & F_735)
		temp = 4;
	else
		temp = 5;
	doublefreq(freq * 1e6, cmd.freq, temp);
	return (setcmda(ident, (u_char *)&cmd, rsp));
}
