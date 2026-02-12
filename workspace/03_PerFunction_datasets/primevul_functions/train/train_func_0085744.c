tcp_newreno_partialack(struct tcpcb *tp, struct tcphdr *th)
{


	tcp_seq onxt = tp->snd_nxt;
	u_long  ocwnd = tp->snd_cwnd;

	TCP_TIMER_DISARM(tp, TCPT_REXMT);
	tp->t_rtttime = 0;
	tp->snd_nxt = th->th_ack;


	tp->snd_cwnd = tp->t_maxseg + (th->th_ack - tp->snd_una);
	(void)tcp_output(tp);
	tp->snd_cwnd = ocwnd;
	if (SEQ_GT(onxt, tp->snd_nxt))
		tp->snd_nxt = onxt;


	if (tp->snd_cwnd > th->th_ack - tp->snd_una)
		tp->snd_cwnd -= th->th_ack - tp->snd_una;
	else
		tp->snd_cwnd = 0;
	tp->snd_cwnd += tp->t_maxseg;
}
